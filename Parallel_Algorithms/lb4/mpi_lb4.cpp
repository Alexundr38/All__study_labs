#include <iostream>
#include <vector>
#include <mpi.h>
#include <random>
#include <fstream>

struct RangValue {
    int rang;
    float value;
};

int main(int argc, char** argv) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib_int(0, 1);
    std::uniform_real_distribution<> distrib_real(-5,5);

    MPI_Init(&argc, &argv);

    int proc_rang, num_proc;
    MPI_Comm_rank(MPI_COMM_WORLD, &proc_rang);
    MPI_Comm_size(MPI_COMM_WORLD, &num_proc);

    int N_flag = proc_rang ? distrib_int(gen) : 1;
    float real_value = 0;
    if (N_flag){
        real_value = distrib_real(gen);
        std::cout << "Start proc rang: " << proc_rang << "; value: " << real_value << "\n";
    }

    double t1, t2, dt;
    t1 = MPI_Wtime();

    MPI_Comm new_comm;
    int color = N_flag ? 0 : MPI_UNDEFINED;

    MPI_Comm_split(MPI_COMM_WORLD, color, proc_rang, &new_comm);

    if (N_flag){
        int new_rang, new_size;
        MPI_Comm_rank(new_comm, &new_rang);
        MPI_Comm_size(new_comm, &new_size);

        MPI_Datatype MPI_RANG_VALUE;
        int blocklengths[2] = {1, 1};
        MPI_Aint displacements[2];
        MPI_Datatype types[2] = {MPI_INT, MPI_FLOAT};

        RangValue temp;
        MPI_Get_address(&temp.rang, &displacements[0]);
        MPI_Get_address(&temp.value, &displacements[1]);
        displacements[1] -= displacements[0];
        displacements[0] = 0;

        MPI_Type_create_struct(2, blocklengths, displacements, types, &MPI_RANG_VALUE);
        MPI_Type_commit(&MPI_RANG_VALUE);

        RangValue sended_data = {new_rang, real_value};
        std::vector<RangValue> all_data(new_size);

        MPI_Allgather(&sended_data, 1, MPI_RANG_VALUE, all_data.data(), 1, MPI_RANG_VALUE, new_comm);

        t2 = MPI_Wtime();
        dt = t2 - t1;
        std::ofstream out("time.txt", std::ios::app);
        out << dt *100000<< "\n";
        out.close();

        if (new_rang == 0){
            for (int i = 1; i < new_size; i++){
                int idx = i;
                while (idx > 0 && all_data[idx].rang > all_data[idx - 1].rang){
                    RangValue temp_data = all_data[idx];
                    all_data[idx] = all_data[idx - 1];
                    all_data[idx - 1] = temp_data;
                    idx--;
                }
            }
            for (const auto& data : all_data) {
                std::cout << "New prog rang " << data.rang << "; value: " << data.value << std::endl;
            }
        }
        
        MPI_Type_free(&MPI_RANG_VALUE);
        MPI_Comm_free(&new_comm);
    }

    MPI_Finalize();
}