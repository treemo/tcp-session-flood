// revision 3

#pragma once

#if defined (WIN32)
//	#include <Windows.h>
	#pragma comment(lib, "pthreadVSE2.lib")
#elif defined (linux)
    #include <unistd.h>
#endif

#include <iostream>
#include <pthread.h>

template <typename T>
class Thread
{
	private:
		pthread_t m_thread;
		bool m_threadRun;

	public:
		Thread(void);
		~Thread(void);
		void startThread();
		void stopThread();
		void threadSleep(int mili);
		void threadUpdate();

	protected:
        static void * threadExecute(void * object);
};

template <typename T>
Thread<T>::Thread(void) : m_threadRun(false)
{
	std::cout << "Thread cree" << std::endl;
	startThread();
}

template <typename T>
Thread<T>::~Thread(void)
{
	std::cout << "Thread detruit" << std::endl;
	stopThread();
}

template <typename T>
void Thread<T>::startThread()
{
	if (m_threadRun)
		return;

	m_threadRun = true;
    pthread_create(&m_thread, NULL, Thread::threadExecute, (void*)this);
}

template <typename T>
void Thread<T>::stopThread()
{
	if (!m_threadRun)
		return;

	m_threadRun = false;
	pthread_cancel(m_thread);
}

template <typename T>
void* Thread<T>::threadExecute(void* object)
{
    Thread* thread = (Thread*)object;
	thread->threadUpdate();

	return NULL;
}

template <typename T>
void Thread<T>::threadSleep(int mili)
{
#if defined (WIN32)
    Sleep(mili);
#elif defined (linux)
	usleep(mili*1000);
#endif
}

template <typename T>
void Thread<T>::threadUpdate()
{
	T* classFille = ((T*)this);

	if(!classFille)
	{
		std::cout << "erreur thread : cast impossible" << std::endl;
		stopThread();
		return;
	}

	while(m_threadRun)
	{
		threadSleep(300);
		classFille->update();
	}
}