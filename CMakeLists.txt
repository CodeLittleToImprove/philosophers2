cmake_minimum_required(VERSION 3.25)
project(Philosophers C)
set(CMAKE_C_STANDARD 99)

add_executable(philo
        src/data_init.c
        src/dinner.c
        src/getter_setter.c
        src/main.c
        src/monitoring.c
        src/monitoring_utils.c
        src/parsing.c
        src/parsing_utils.c
        src/safe_function_handler.c
        src/time.c
        src/utils.c
        src/write_status.c
)
