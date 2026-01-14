#include <iostream>
#include <mpi.h>

int main(int argc, char** argv){
    
    MPI_Init(&argc, &argv);

    int proc_rang, recv_rang, num_proc;
    MPI_Comm_rank(MPI_COMM_WORLD, &proc_rang);
    MPI_Comm_size(MPI_COMM_WORLD, &num_proc);

    double t1, t2, dt;
    t1 = MPI_Wtime();
    
    if (proc_rang != 0){
        MPI_Send(&proc_rang, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
    }
    else {
        std::cout << "in work process with rang " << proc_rang << "\n";
        MPI_Status status;

        for (int i = 1; i < num_proc; i++){
            MPI_Recv(&recv_rang, 1, MPI_INT, i, 0, MPI_COMM_WORLD, &status);
            std::cout << "recieved message from process with rang " << recv_rang << "\n";
        }
    }

    t2 = MPI_Wtime();
    dt = t2 - t1;
    std::cout << dt * 100000 << "\n";

    MPI_Finalize();
}