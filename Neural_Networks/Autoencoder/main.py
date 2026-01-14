import tensorflow as tf
import matplotlib.pyplot as plt
from tensorflow.keras import models, losses, layers
from tensorflow.keras.optimizers import Adam
from tensorflow.keras.datasets import cifar10
from tensorflow.keras.layers import Conv2D, BatchNormalization, Conv2DTranspose, Reshape, Flatten, Dense, Input, Layer, MaxPooling2D
from tensorflow.keras import Model
import numpy as np
# from sklearn.decomposition import PCA

(x_train, y_train), (x_test, y_test) = cifar10.load_data()

class Sampling(Layer):
    def __init__(self, latent_dim=64):
        super(Sampling, self).__init__()
        self.latent_dim = latent_dim
    def call(self, inputs):
        mu, log_var = inputs
        epsilon = tf.random.normal(shape=(tf.shape(mu)[0], self.latent_dim))
        return mu + tf.sqrt(abs(log_var)) * epsilon

class VAE(Model):
    def __init__(self, latent_dim=64, **kwargs):
        super(VAE, self).__init__(**kwargs)
        self.latent_dim = latent_dim
        self.encoder = self._build_encoder()
        self.decoder = self._build_decoder()
        self.mse = losses.MeanSquaredError()
        # self.reconstruction_loss = losses.BinaryCrossentropy()

        self.total_loss_tracker = tf.keras.metrics.Mean(name="total_loss")
        self.reconstruction_loss_tracker = tf.keras.metrics.Mean(
            name="reconstruction_loss"
        )
        self.kl_loss_tracker = tf.keras.metrics.Mean(name="kl_loss")
        self.mu_mean_tracker = tf.keras.metrics.Mean(name="mu_mean")
        self.log_var_mean_tracker = tf.keras.metrics.Mean(name="log_var_mean")

    def _build_encoder(self):
        encoder_inputs = Input(shape=(32, 32, 3))
        x = Conv2D(32, 3, padding="same", activation="relu")(encoder_inputs)
        x = BatchNormalization(x)
        x = Conv2D(32, 3, padding="same", activation="relu")(encoder_inputs)
        x = MaxPooling2D()(x)
        # x = layers.LeakyReLU()(x)
        # x = BatchNormalization()(x)
        x = Conv2D(64, 3, padding="same", activation="relu")(x)
        x = BatchNormalization()(x)
        x = Conv2D(64, 3, padding="same", activation="relu")(x)
        x = MaxPooling2D()(x)
        # x = layers.LeakyReLU()(x)
        # x = Conv2D(64, 3, padding="same", activation="relu")(x)
        # x = Conv2D(64, 3, padding="same", activation="relu")(x)
        # x = BatchNormalization()(x)
        x = Conv2D(128, 3, padding="same", activation="relu")(x)
        x = BatchNormalization(x)
        x = Conv2D(64, 3, padding="same", activation="relu")(x)
        x = MaxPooling2D()(x)
        # x = layers.LeakyReLU()(x)
        x = Flatten()(x)
        x = Dense(256)(x)
        mu = Dense(self.latent_dim)(x)
        log_var = Dense(self.latent_dim)(x)
        z = Sampling()([mu, log_var])
        return Model(encoder_inputs, [mu, log_var, z], name="encoder")

    def _build_decoder(self):
        latent_inputs = Input(shape=(self.latent_dim,))
        x = Dense(4*4*128, activation="relu")(latent_inputs)
        x = Reshape((4, 4, 128))(x)
        x = Conv2DTranspose(128, 3, strides=2, padding="same", activation="relu")(x)
        x = Conv2DTranspose(128, 3, padding="same", activation="relu")(x)
        x = BatchNormalization()(x)
        x = Conv2DTranspose(64, 3, strides=2, padding="same", activation="relu")(x)
        x = Conv2DTranspose(64, 3, padding="same", activation="relu")(x)
        x = BatchNormalization()(x)
        x = Conv2DTranspose(32, 3, strides=2, padding="same", activation="relu")(x)
        x = Conv2DTranspose(32, 3, padding="same", activation="relu")(x)
        # x = layers.LeakyReLU()(x)
        # x = Conv2DTranspose(128, 3, padding="same", activation="relu")(x)
        x = BatchNormalization()(x)
        # x = Conv2DTranspose(64, 3, strides=2, padding="same", activation="relu")(x)
        # x = layers.LeakyReLU()(x)
        # x = Conv2DTranspose(64, 3, padding="same", activation="relu")(x)
        # x = Conv2DTranspose(32, 3, strides=2, padding="same", activation="relu")(x)
        decoder_outputs = Conv2DTranspose(3, 3, padding="same", activation="tanh")(x)
        return Model(latent_inputs, decoder_outputs, name="decoder")

    @property
    def metrics(self):
        return [
            self.total_loss_tracker,
            self.reconstruction_loss_tracker,
            self.kl_loss_tracker,
        ]

    def loss_func(self, expect, result, mu, log_var, betta = 1.0):
      mse_value = self.mse(expect, result)
      KL_distance =  tf.reduce_mean(tf.reduce_sum(-0.5 * (1 + log_var - tf.square(mu) - tf.exp(log_var)), axis=1))
      return mse_value + betta * KL_distance, mse_value, KL_distance

    def train_step(self, data):
      noisy_images, original_images = data

      with tf.GradientTape() as tape:
          mu, log_var, z = self.encoder(noisy_images)
          # print(mu, log_var, z)
          reconstruction = self.decoder(z)
          # log_var = tf.clip_by_value(log_var, -10, 10)
          # print(noisy_images, original_images, reconstruction)
          total_loss, mse_value, kl_distance = self.loss_func(original_images, reconstruction, mu, log_var, betta=0.1)

      grads = tape.gradient(total_loss, self.trainable_weights)
      self.optimizer.apply_gradients(zip(grads, self.trainable_weights))

      self.total_loss_tracker.update_state(total_loss)
      self.reconstruction_loss_tracker.update_state(mse_value)
      self.kl_loss_tracker.update_state(kl_distance)
      self.mu_mean_tracker.update_state(tf.reduce_mean(mu))
      self.log_var_mean_tracker.update_state(tf.reduce_mean(log_var))

      return {
          "loss": self.total_loss_tracker.result(),
          "reconstruction_loss": self.reconstruction_loss_tracker.result(),
          "kl_loss": self.kl_loss_tracker.result(),
          "mu_mean": self.mu_mean_tracker.result(),
          "log_var_mean": self.log_var_mean_tracker.result(),
      }

    def call(self, inputs):
        mu, log_var, z = self.encoder(inputs)
        reconstructed = self.decoder(z)
        return reconstructed
    
vae = VAE(latent_dim=64)
vae.compile(optimizer=Adam(learning_rate=1e-3))

x_train_new = (x_train.astype('float32') - 128.0) / 128.0
# x_test_new = x_test.astype('float32') / 255.0
# x_train_new = x_train

noise_factor = 0.2
x_train_noisy = x_train_new + noise_factor * tf.random.normal(shape=x_train_new.shape)
x_train_noisy = tf.clip_by_value(x_train_noisy, -1.0, 1.0)

history = vae.fit(
    x_train_noisy, x_train_new,
    # validation_data=(x_test_noisy, x_test),
    epochs=50,
    batch_size=128
)

num_examples = 5
test_samples = x_train_new[:num_examples]

# Реконструируем
reconstructions = vae.predict(test_samples)

# Отображение
plt.figure(figsize=(15, 5))
for i in range(num_examples):
    # Зашифрованное изображение
    plt.subplot(3, num_examples, i + 1)
    plt.imshow(test_samples[i])
    plt.title("Noisy")
    plt.axis("off")

    # Реконструкция
    plt.subplot(3, num_examples, num_examples + i + 1)
    plt.imshow(reconstructions[i])
    plt.title("Reconstructed")
    plt.axis("off")

    # Оригинал
    plt.subplot(3, num_examples, 2*num_examples + i + 1)
    plt.imshow(x_train[i])
    plt.title("Original")
    plt.axis("off")

plt.tight_layout()
plt.show()