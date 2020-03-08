shell: \
			main.o \
			display_shell_prompt.o \
			get_status.o \
			exec_cd.o \
			display_shell_prompt.o \
			string_splitter.o \
			interpret_command.o \
			exec_ls.o \
			exec_cd.o \
			exec_env.o \
			exec_pinfo.o \
			exec_jobs.o \
			exec_fg_bg_kjob.o \
			exec_cronjob.o \
			isvalid_redirection.o \
			redirect_handler.o \
			pipe_handler.o
	$(CC) -g -o shell $^  -L/usr/local/lib -I/usr/local/include -lreadline -Wall 

clean:
	@rm -f *.o shell

main.o: shell.h main.c
	$(CC) -g -c main.c  -L/usr/local/lib -I/usr/local/include -lreadline -Wall 

display_shell_prompt.o: shell.h display_shell_prompt.c
	$(CC) -g -c display_shell_prompt.c

exec_cd.o: shell.h exec_cd.c
	$(CC) -g -c exec_cd.c

exec_ls.o: shell.h exec_ls.c
	$(CC) -g -c exec_ls.c

exec_pinfo.o: shell.h exec_pinfo.c
	$(CC) -g -c exec_pinfo.c

exec_env.o: shell.h exec_env.c
	$(CC) -g -c exec_env.c

exec_jobs.o: shell.h exec_jobs.c
	$(CC) -g -c exec_jobs.c

exec_fg_bg_kjob.o: shell.h exec_fg_bg_kjob.c
	$(CC) -g -c exec_fg_bg_kjob.c

exec_cronjob.o: shell.h exec_cronjob.c
	$(CC) -g -c exec_cronjob.c

string_splitter.o: shell.h string_splitter.c
	$(CC) -g -c string_splitter.c

interpret_command.o: shell.h interpret_command.c
	$(CC) -g -c interpret_command.c

isvalid_redirection.o: shell.h isvalid_redirection.c
	$(CC) -g -c isvalid_redirection.c

redirect_handler.o: shell.h redirect_handler.c
	$(CC) -g -c redirect_handler.c

pipe_handler.o: shell.h pipe_handler.c
	$(CC) -g -c pipe_handler.c

get_status.o: shell.h get_status.c
	$(CC) -g -c get_status.c