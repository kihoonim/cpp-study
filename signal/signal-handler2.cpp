#include <iostream>
#include <csignal>
#include <csetjmp>

using namespace std;

jmp_buf gBuffer;        // A buffer to hold info on where to jump to

void catch_signal(int signalNumber)
{
	//signal(SIGINT, SIG_DFL);          // Switch to default handling
	signal(SIGINT, catch_signal);       // Reactivate this handler.

	longjmp             // Jump back into the normal flow of the program
	(
		gBuffer,        // using this context to say where to jump to
		signalNumber    // and passing back the value of the signal.
	);
}


int test_signal()
{
	signal(SIGINT, catch_signal);

	try
	{
		int sig;
		if ((sig = setjmp(gBuffer)) == 0)
		{
			cout << "before raise\n";
			raise(SIGINT);
			cout << "after raise\n";

		}
		else
		{
			// This path implies that a signal was thrown, and
			// that the setjmp function returned the signal
			// which puts use at this point.

			// Now that we are out of the signal handler it is
			// normally safe to throw what ever sort of exception we want.
			throw(sig);
		}
	}
	catch (int& z)
	{
		cerr << "Caught exception: " << z << endl;
	}

	return 0;
}

int main()
{
	try
	{
		test_signal();
	}
	catch (int& z)
	{
		cerr << "Caught unexpected exception: " << z << endl;
	}
	return 0;
}