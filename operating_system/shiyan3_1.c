
/******************************************************************************
 *并发进程间通过管道实现数据实时传送 父进程准备好读、写缓冲区，创建一个无名管道；
 * 父进程分别创建两个子进程； 
 * 每个子进程通过管道分别向父进程传送一个(<=50字符的)字符串，然后结束； 
 *父进程等待子进程传来的数据，从管道中接收到数据后，将字符串从屏幕上显示出来，然后结束。
 ******************************************************************************/
 
 
 #include <stdio.h>
 #include <unistd.h> 			//fork(),pipe()
 #include <string.h>
 #include <stdlib.h>
 #include <sys/wait.h>
 
 
 int main(void)
 {
 	int		pipefd[2] = {0};
 	pid_t 	c1_pid;
 	pid_t 	c2_pid;
 	char	ch_input[50] = {0};
 	char 	ch_output[50] = {0};
 	
 	if (pipe(pipefd) == -1) 			//创建一个管道
 	{
 		perror("pipe");
 		exit(EXIT_FAILURE);
 	}
 	
 	if ((c1_pid = fork()) == -1) 		//child 1 create
 	{
 		perror("fork");
 		exit(EXIT_FAILURE);
 	}
 	
 	if (c1_pid == 0) 					//child 1
 	{
 		//写一个字符串到管道
// 		ch_input = "child 11111";
 		memcpy(ch_input, "child 11111", 15);
 		
 		lockf(pipefd[1], 1, 0); 			//1为锁定， 0为从文件头到文件尾
 		close(pipefd[0]); 					//close unused read end	
 		write(pipefd[1], ch_input, strlen(ch_input));
 		close(pipefd[1]);
 		lockf(pipefd[1], 0, 0);
 		
 	 	exit(EXIT_SUCCESS);	 		
 								
 	}
 	else  									//parent
 	{
 		if ((c2_pid = fork()) == -1) 		//child 2 create
	 	{
	 		perror("fork"); 				
	 		exit(EXIT_FAILURE);
	 	}
	 	
	 	if (c2_pid == 0) 					//child 2
	 	{
	 		//写一个字符串到管道

//	 		ch_input = "child 22222";
 			memcpy(ch_input, "child 22222", 15);
 				 		
	 		lockf(pipefd[1], 1, 0); 			//1为锁定， 0为从文件头到文件尾
	 		close(pipefd[0]); 					//close unused read end	
	 		write(pipefd[1], ch_input, strlen(ch_input));
	 		close(pipefd[1]);
	 		lockf(pipefd[1], 0, 0);
	 		
	 		exit(EXIT_SUCCESS);	 		
		 		
	 	}
	 	else 								//parent
	 	{
	 		close(pipefd[1]);
	 		
	 		while (read(pipefd[0], ch_output, 50) > 0) 		//读50个
	 		{
	 			write(STDOUT_FILENO, ch_output, strlen(ch_output+1));
	 			write(STDOUT_FILENO, "\n", 1);
	 		}
	 		

	 		while (read(pipefd[0], ch_output, 50) > 0) 		//读50个
	 		{
	 			write(STDOUT_FILENO, ch_output, strlen(ch_output+1));
	 			write(STDOUT_FILENO, "\n", 1);
	 		}
	 		
	 		
	 		close(pipefd[0]);
	 		
	 		wait(NULL);
	 		wait(NULL);
	 		exit(EXIT_SUCCESS);	 		
	 		
	 	}
 	}
 	
 	
 	
 	
 }
