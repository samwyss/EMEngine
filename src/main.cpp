#include <mpi.h>

//! main driver function and build target
//! \param argc argument count
//! \param argv argument vector
//! \return
int main(int argc, char** argv) {
	// initialize MPI environment
	MPI_Init(&argc, &argv);

	/// number of processes in MPI_COMM_WORLD communicator
	int world_size;
	MPI_Comm_size(MPI_COMM_WORLD, &world_size);

	/// rank inside of MPI_COMM_WORLD communicator
	int world_rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);



    // terminate MPI environment
    MPI_Finalize();
}