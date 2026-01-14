#include <iostream>
#include <mpi.h>
#include <vector>
#include <string>
#include <random>
#include <algorithm>

int main(int argc, char** argv){
    std::vector<std::vector<std::string>> values = {{"яблоко", "каша", "помидорка"}, {"гвоздь","телефон","бетон"}};
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib_category(0,1);
    std::uniform_int_distribution<> distrib_value(0,2);

    MPI_Init(&argc, &argv);

    int proc_rang, num_proc;

    MPI_Comm_rank(MPI_COMM_WORLD, &proc_rang);
    MPI_Comm_size(MPI_COMM_WORLD, &num_proc);

    double t1, t2, dt;
    t1 = MPI_Wtime();

    if (num_proc > 1){
        if (proc_rang == 0){
            for (int i = 1; i < num_proc; i++){
                int category = distrib_category(gen);
                int value = distrib_value(gen);
                std::string word = values[category][value];

                MPI_Send(word.c_str(), word.length() + 1, MPI_CHAR, i, 0, MPI_COMM_WORLD);
                //std::cout << "0 proccess send \"" << word << "\" to proccess " << i << "\n";

                char response[50];
                MPI_Recv(response, 50, MPI_CHAR, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                //std::cout << i << " proccess send \"" << response << "\" to 0 proccess\n";
            }
        }
        else{
            char response[50];
            MPI_Recv(response, 50, MPI_CHAR, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            
            auto it = std::find(values[0].begin(), values[0].end(), response);

            std::string word = (it !=values[0].end()) ? "съедобное" : "несъедобное";
            MPI_Send(word.c_str(), word.length() + 1, MPI_CHAR, 0, 0, MPI_COMM_WORLD);
        }
    }

    t2 = MPI_Wtime();
    dt = t2 - t1;
    std::cout << dt << "\n";

    MPI_Finalize();
}