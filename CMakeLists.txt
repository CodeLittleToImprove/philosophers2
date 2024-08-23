cmake_minimum_required(VERSION 3.25)
project(Philosophers C)
set(CMAKE_C_STANDARD 99)

add_executable(philo
        src/main.c
        src/utils.c
        src/parsing.c
#        src/dinner.c
#        src/dinner.c
#        src/getter_setter.c
#        src/synchro_utils.c
        src/data_init.c
        src/safe_function_handler.c
        src/dinner.c
        src/time.c
        #        src/write_status.c
#        src/monitoring.c
)
