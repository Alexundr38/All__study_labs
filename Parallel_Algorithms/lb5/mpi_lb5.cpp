#include <iostream>
#include <mpi.h>
#include <fstream>

int main(int argc, char* argv[]){
    
    MPI_Init(&argc, &argv);
    
    int proc_rang, num_proc;

    float value, received_value;

    MPI_Comm_rank(MPI_COMM_WORLD, &proc_rang);
    MPI_Comm_size(MPI_COMM_WORLD, &num_proc);

    if (num_proc % 2 != 0){
        if (proc_rang == 0){
            printf("Error: Number of processes must be even\n");
        }
        MPI_Finalize();
        return 0;
    }

    if (proc_rang == 0){
        value = 10.5f;
    } else if (proc_rang == 1){
        value = 20.7f;
    }

    int dims[2], periods[2], coords[2];
    dims[0] = num_proc / 2;
    dims[1] = 2;
    periods[0] = 0;
    periods[1] = 0;

    int remain_dims[2];
    remain_dims[0] = 1;
    remain_dims[1] = 0;

    MPI_Comm cart_comm, column_comm;

    double t1, t2, dt;
    t1 = MPI_Wtime();

    MPI_Cart_create(MPI_COMM_WORLD, 2, dims, periods, 0, &cart_comm);

    MPI_Cart_coords(cart_comm, proc_rang, 2, coords);

    MPI_Cart_sub(cart_comm, remain_dims, &column_comm);

    int new_rang, new_size;
    MPI_Comm_rank(column_comm, &new_rang);
    MPI_Comm_size(column_comm, &new_size);

    bool is_root_in_column = (coords[0] == 0);

    if (is_root_in_column){
        MPI_Bcast(&value, 1, MPI_FLOAT, 0, column_comm);
        received_value = value;
    } else {
        MPI_Bcast(&received_value, 1, MPI_FLOAT, 0, column_comm);
    }

    t2 = MPI_Wtime();
    dt = t2 - t1;
    std::ofstream out("time.txt", std::ios::app);
    out << dt << "\n";

    out.close();

    std::cout << "Process number " << proc_rang << " (coords[" << coords[0] << "," 
              << coords[1] << "]) received value = " << received_value << "\n";

    MPI_Comm_free(&column_comm);
    MPI_Comm_free(&cart_comm);

    MPI_Finalize();
    return 0;
}