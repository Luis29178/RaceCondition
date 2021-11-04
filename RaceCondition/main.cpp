///////////////////////////////////////////////////////////////////////////////////
// TODO: #include any files need
///////////////////////////////////////////////////////////////////////////////////

// Include file and line numbers for memory leak detection for visual studio in debug mode
#if defined _MSC_VER && defined _DEBUG
	#include <crtdbg.h>
	#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)
	#define ENABLE_LEAK_DETECTION() _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF)
#else
	#define ENABLE_LEAK_DETECTION()
#endif
#include <cstdio>
#include <cstdlib>
#include <thread>
#include <vector>
#include <thread>
#include <map>

struct ThreadStruct
{
	// ID of the thread
	int id;
	// Length of the shared string
	int sharedStringLength;
	// Number of strings a single thread will generate
	int numberOfStringsToGenerate;
	// Shared string that will be generate in each thread. This memory is shared among all threads.
	char *sharedString;
	
	///////////////////////////////////////////////////////////////////////////////////
	// TODO: Add any extra variables needed by the threads here
	///////////////////////////////////////////////////////////////////////////////////	
	int runtype;
};

///////////////////////////////////////////////////////////////////////////////////////////
// Prompts the user to press enter and waits for user input
///////////////////////////////////////////////////////////////////////////////////////////
void Pause()
{
	printf("Press enter to continue\n");
	getchar();
}

///////////////////////////////////////////////////////////////////////////////////
// Entry point for worker threads. 
//
// Arguments:
//   threadData - Pointer to per-thread data for this thread.
///////////////////////////////////////////////////////////////////////////////////

void ThreadEntryPoint(ThreadStruct *threadData)
{
	///////////////////////////////////////////////////////////////////////////////////
	// TODO: Add code to this function to make it run according to the run type.
	//		 However do NOT duplicate the following code.
	///////////////////////////////////////////////////////////////////////////////////	
	for (int i = 0; i < threadData->numberOfStringsToGenerate; i++, std::this_thread::sleep_for(std::chrono::milliseconds(10)))
	{
		for (int j = 0; j < threadData->sharedStringLength; j++)
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(1));
			threadData->sharedString[j] = 'A' + threadData->id;
		}
		printf("Thread %d: %s\n", threadData->id, threadData->sharedString);
	}
	//Switch will choose runtype
	switch (threadData->runtype)
	{
	case 0:

		break;
	case 1:

		break;
	case 2:

		break;
	case 3:

		break;

	}
	

	///////////////////////////////////////////////////////////////////////////////////
}


int main(int argc, char** argv)
{
	ENABLE_LEAK_DETECTION();

	int threadCount = 0;
	int sharedStringLength = 0;
	int numberOfStringsToGenerate = 0;
	int runType = 0;
	char *sharedString = nullptr;
	ThreadStruct *perThreadData = nullptr;



	if (argc != 5)
	{
		fprintf(stderr, "Error: missing or incorrect command line arguments\n\n"); 
		fprintf(stderr, "Usage: RaceCondition threadCount sharedStringLength numberOfStringsToGenerate runType\n\n");
		fprintf(stderr, "Arguments:\n");
		fprintf(stderr, "    threadCount                  Number of threads to create.\n");
		fprintf(stderr, "    sharedStringLength           Length of string to generate.\n");
		fprintf(stderr, "    numberOfStringsToGenerate    Number of strings to generate per thread.\n");
		fprintf(stderr, "    runType                      The run type.\n\n");
		Pause();
		return 1;
	}
	//pulls arguments from command line
	//{CL: 0|xx.exe|1|threadCount|2|sharedStringLength|3|numberOfStringsToGenerate|4|runtype|}
	threadCount = atoi(argv[1]);
	sharedStringLength = atoi(argv[2]);
	numberOfStringsToGenerate = atoi(argv[3]);
	runType = atoi(argv[4]);
	//

	if(threadCount < 0 || sharedStringLength < 0 || numberOfStringsToGenerate < 0 || runType < 0)
	{
		fprintf(stderr, "Error: All arguments must be positive integer values.\n");
		Pause();
		return 1;
	}

	printf("%d thread(s), string sharedStringLength %d, %d iterations, %d runType\n",
		threadCount, sharedStringLength, numberOfStringsToGenerate, runType);
	
	sharedString = new char[sharedStringLength + 1];
	memset(sharedString, 0, sharedStringLength + 1);
	perThreadData = new ThreadStruct[threadCount];
	
	///////////////////////////////////////////////////////////////////////////////////
	// TODO:: You will need a container to store the thread class objects. It is up to you
	//   to decide how you want to store the threads.
	///////////////////////////////////////////////////////////////////////////////////	
	std::vector<std::thread> threadmap;

	// NOTE: Do NOT change this for loop header
	for (int i = threadCount - 1; i >= 0; i--)
	{
		perThreadData[i].id = i;
		perThreadData[i].sharedStringLength = sharedStringLength;
		perThreadData[i].numberOfStringsToGenerate = numberOfStringsToGenerate;
		perThreadData[i].sharedString = sharedString;
		
		///////////////////////////////////////////////////////////////////////////////////
		// TODO:: Setup any additional variables in perThreadData and start the threads.
		//			MUST be done in this for loop.
		///////////////////////////////////////////////////////////////////////////////////
		perThreadData[i].runtype = runType;


		//places perthreaddata [KEY] and worker [THREAD] into a threadmap 
		
		threadmap.push_back(std::thread(ThreadEntryPoint, perThreadData));
		
	}


	///////////////////////////////////////////////////////////////////////////////////
	// TODO:: Wait for all of the threads to finish. Since we are using
	//   Joinable threads we must Join each one. Joining a thread will cause
	//   the calling thread (main in this case) to block until the thread being
	//   joined has completed executing.
	///////////////////////////////////////////////////////////////////////////////////


	for (auto& thread : threadmap)
	{
		thread.join();
	}

	Pause();
	
	///////////////////////////////////////////////////////////////////////////////////
	// TODO: Clean up
	///////////////////////////////////////////////////////////////////////////////////
	delete perThreadData;
	delete sharedString;

	return 0;
}
