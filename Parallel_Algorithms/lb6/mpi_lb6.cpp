#include <iostream>
#include <vector>
#include <mpi.h>
#include <fstream>


void matrix_multiply(const std::vector<std::vector<int>>& first,
                     const std::vector<std::vector<int>>& second,
                     std::vector<std::vector<int>>& result, int m_size) {
    for (int i = 0; i < m_size; i++) {
        for (int j = 0; j < m_size; j++) {
            result[i][j] = 0;
            for (int k = 0; k < m_size; k++) {
                result[i][j] += first[i][k] * second[k][j];
            }
        }
    }
}

void row_matrix_multiply(const std::vector<std::vector<int>>& first_local,
                         const std::vector<std::vector<int>>& second,
                         std::vector<std::vector<int>>& result_local, int m_size, int local_rows) {
    for (int i = 0; i < local_rows; i++) {
            for (int j = 0; j < m_size; j++) {
                result_local[i][j] = 0;
                for (int k = 0; k < m_size; k++) {
                    result_local[i][j] += first_local[i][k] * second[k][j];
                }
            }
        }
}


void initialize_matrix(std::vector<std::vector<int>>& matrix, int m_size) {
    for (int i = 0; i < m_size; i++) {
        for (int j = 0; j < m_size; j++) {
            matrix[i][j] = rand() % 10;
        }
    }
}


void input_matrix(std::vector<std::vector<int>>& matrix, int m_size, int matrix_num) {
    std::cout << "Enter matrix " << matrix_num << " (" << m_size << "x" << m_size << ") row by row:" << std::endl;
    for (int i = 0; i < m_size; i++) {
        std::cout << "Row " << i + 1 << ": ";
        for (int j = 0; j < m_size; j++) {
            std::cin >> matrix[i][j];
        }
    }
}


void print_matrix(const std::vector<std::vector<int>>& matrix, int m_size) {
    for (int i = 0; i < m_size; i++) {
        for (int j = 0; j < m_size; j++) {
            std::cout << matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

bool check_equal(const std::vector<std::vector<int>>& first,
                 const std::vector<std::vector<int>>& second,
                 int m_size){
    for (int i = 0; i < m_size; i++) {
        for (int j = 0; j < m_size; j++) {
            if (first[i][j] != second[i][j]) {
                return false;
            }
        }
    }
    return true;
}


void compute_rows(int& start_row, int& end_row, int& local_rows, 
                  int current_number, int rows_per_process, int remainder) {
    if (current_number < remainder) {
        local_rows = rows_per_process + 1;
        start_row = current_number * local_rows;
    } else {
        local_rows = rows_per_process;
        start_row = remainder * (rows_per_process + 1) + (current_number - remainder) * rows_per_process;
    }
    end_row = start_row + local_rows;
}


void parse_arguments(int argc, char* argv[], int& m_size, bool& is_print, bool& is_input) {
    m_size = 6; 
    is_print = false;
    is_input = false;
    
    for (int i = 1; i < argc; i++) {
        std::string arg = argv[i];
        if (arg == "-s" && i + 1 < argc) {
            m_size = std::atoi(argv[i + 1]);
            i++;
        } else if (arg == "-p") {
            is_print = true;
        } else if (arg == "-i") {
            is_input = true;
        }
    }
}


int main(int argc, char* argv[]) {
    MPI_Init(&argc, &argv);
    
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    
    int m_size = 6;
    bool is_print, is_input;
    parse_arguments(argc, argv, m_size, is_print, is_input);
    
    int dims[1] = {size};
    int periods[1] = {0};
    MPI_Comm grid_comm;
    MPI_Cart_create(MPI_COMM_WORLD, 1, dims, periods, 0, &grid_comm);
    
    int grid_rank;
    MPI_Comm_rank(grid_comm, &grid_rank);
    
    int rows_per_process = m_size / size;
    int remainder = m_size % size;
    
    int start_row, end_row, local_rows;
    compute_rows(start_row, end_row, local_rows, grid_rank, rows_per_process, remainder);
    
    if (rank == 0) {
        std::cout << "Matrix size: " << m_size << "x" << m_size << std::endl;
        std::cout << "Number of processes: " << size << std::endl;
    }
    
    if (rank == 0) {
        std::vector<std::vector<int>> first(m_size, std::vector<int>(m_size));
        std::vector<std::vector<int>> second(m_size, std::vector<int>(m_size));
        std::vector<std::vector<int>> result_seq(m_size, std::vector<int>(m_size));
        
        if (is_input) {
            input_matrix(first, m_size, 1);
            input_matrix(second, m_size, 2);
        } else {
            initialize_matrix(first, m_size);
            initialize_matrix(second, m_size);
        }

        if (is_print) {
            std::cout << "Matrix A:" << std::endl;
            print_matrix(first, m_size);
            std::cout << "Matrix B:" << std::endl;
            print_matrix(second, m_size);
        }
        
        double start_time = MPI_Wtime();
        matrix_multiply(first, second, result_seq, m_size);
        double end_time = MPI_Wtime();
        
        std::cout << "Sequential time: " << (end_time - start_time) * 1000 << " ms" << std::endl;

        // std::ofstream out1("time_1.txt", std::ios::app);
        // out1 << (end_time - start_time) * 1000<< "\n";
        // out1.close();
        
        for (int i = 0; i < m_size; i++) {
            MPI_Bcast(second[i].data(), m_size, MPI_INT, 0, grid_comm);
        }
        
        for (int dest = 1; dest < size; dest++) {
            int dest_start, dest_end, dest_rows;
            compute_rows(dest_start, dest_end, dest_rows, dest, rows_per_process, remainder);

            for (int i = dest_start; i < dest_end; i++) {
                MPI_Send(first[i].data(), m_size, MPI_INT, dest, 0, grid_comm);
            }
        }
        
        std::vector<std::vector<int>> first_local(local_rows, std::vector<int>(m_size));
        std::vector<std::vector<int>> result_local(local_rows, std::vector<int>(m_size));
        
        for (int i = 0; i < local_rows; i++) {
            first_local[i] = first[start_row + i];
        }
        
        start_time = MPI_Wtime();
        row_matrix_multiply(first_local, second, result_local, m_size, local_rows);
        
        std::vector<std::vector<int>> result_par(m_size, std::vector<int>(m_size));
        
        for (int i = 0; i < local_rows; i++) {
            result_par[start_row + i] = result_local[i];
        }
        
        for (int src = 1; src < size; src++) {
            int src_start, src_end, src_rows;
            compute_rows(src_start, src_end, src_rows, src, rows_per_process, remainder);
            
            for (int i = src_start; i < src_end; i++) {
                MPI_Recv(result_par[i].data(), m_size, MPI_INT, src, 0, grid_comm, MPI_STATUS_IGNORE);
            }
        }
        end_time = MPI_Wtime();
        
        std::cout << "Parallel time: " << (end_time - start_time) * 1000 << " ms" << std::endl;

        // std::ofstream out2("time_n.txt", std::ios::app);
        // out2 << (end_time - start_time) * 1000 << "\n";
        // out2.close();
        
        if (is_print) {
            std::cout << "Matrix seq:" << std::endl;
            print_matrix(result_seq, m_size);
            std::cout << "Matrix par:" << std::endl;
            print_matrix(result_par, m_size);
        }

        bool correct = check_equal(result_seq, result_par, m_size);
        std::cout << "Result is " << (correct ? "CORRECT" : "INCORRECT") << std::endl;
        
    } else {
        std::vector<std::vector<int>> second(m_size, std::vector<int>(m_size));
        for (int i = 0; i < m_size; i++) {
            MPI_Bcast(second[i].data(), m_size, MPI_INT, 0, grid_comm);
        }
        
        std::vector<std::vector<int>> first_local(local_rows, std::vector<int>(m_size));
        std::vector<std::vector<int>> result_local(local_rows, std::vector<int>(m_size));
        
        for (int i = 0; i < local_rows; i++) {
            MPI_Recv(first_local[i].data(), m_size, MPI_INT, 0, 0, grid_comm, MPI_STATUS_IGNORE);
        }
        
        row_matrix_multiply(first_local, second, result_local, m_size, local_rows);
        
        for (int i = 0; i < local_rows; i++) {
            MPI_Send(result_local[i].data(), m_size, MPI_INT, 0, 0, grid_comm);
        }
    }
    
    MPI_Comm_free(&grid_comm);
    MPI_Finalize();
    return 0;
}