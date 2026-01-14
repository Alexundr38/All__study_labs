#include <iostream>
#include <vector>
#include <mpi.h>
#include <random>
#include <fstream>

struct{
    int value;
    int rang;
} typedef IntInt;

int main(int argc, char** argv) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(-100, 100);

    MPI_Init(&argc, &argv);

    int proc_rang, num_proc;
    std::vector<IntInt> values;
    std::vector<IntInt> final_values;

    MPI_Comm_rank(MPI_COMM_WORLD, &proc_rang);
    MPI_Comm_size(MPI_COMM_WORLD, &num_proc);

    int count = num_proc + 5;
    final_values.resize(count);

    for (int i = 0; i < count; i++){
        IntInt value {distrib(gen), proc_rang};
        values.push_back(value);
    }

    double t1, t2, dt;
    t1 = MPI_Wtime();

    MPI_Reduce(values.data(), final_values.data(), count, MPI_2INT, MPI_MAXLOC, 0, MPI_COMM_WORLD);

    t2 = MPI_Wtime();
    dt = t2 - t1;
    std::ofstream out("time.txt", std::ios::app);
    out << dt *100000<< "\n";
    out.close();

    if (proc_rang == 0){
        std::cout << "Max:";
        for (int i = 0; i < count; i++){
            std::cout << " " << final_values[i].value;
        }
        std::cout << "\nRang:";
        for (int i = 0; i < count; i++){
            std::cout << " " << final_values[i].rang;
        }
        std::cout << '\n';
    }

    MPI_Finalize();
}