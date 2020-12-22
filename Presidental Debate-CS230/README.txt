Name: Pham Minh Nghia
SID: 32507133
				PRESIDENTAL DEBATE

Overview: The project is straight-forward. I just followed the instructions from project description. 
	However, positioning sem_wait and sem_post is quite tricky.
	There are 202 threads: 200 phone call threads, 1 timing thread, and 1 main thread.
	My code satisfy every requirements. 

Phonecall Thread: line 15-64
	line 17-19: taking id.
	line 22-33: connect to available line.
	line 36-48: connect to available operator.
	line 52-55: operator leaves.
	line 58-61: caller leaves.
	Note: operator leaves and caller leaves are different processes. As a result, operator can leave before the line closed.

Timer Thread: line 65-70
	taking input and exit after length of input.

Main_thread Thread: line 72-85
	taking input.
	creating timing thread.
	creating phonecall thread.
	join phonecall thread.

Main Function: line 87-105
	taking and convert input.
	creating semaphores for id, operator, and connected line.
	creating and joing main_thread.
	destroy semaphores and thread.

youtube link: https://www.youtube.com/watch?v=7aHGzTGeGa8 
