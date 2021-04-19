    .model small
    .stack 256
    .data
    .code
    include rlib.inc
start:
    call rlib_showtime
    call rlib_exit
end start
end
