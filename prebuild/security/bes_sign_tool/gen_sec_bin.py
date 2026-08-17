#!/usr/bin/env python
# -*- coding: utf-8 -*-
import os
import sys
import time
import hashlib
import struct

def message(level, msg):
    if isinstance(msg, str) and not msg.endswith('\n'):
        msg += '\n'
    return '[GEN SIGN BIN {}] {}'.format(level.upper(), msg)

def message_line(level, msg):
    for line in msg.splitlines():
        sys.stdout.write(message(level, line))
        sys.stdout.flush()


def sign_info(msg):
    level = 'info'
    message_line(level, msg)


def sign_warning(msg):
    level = 'warning'
    message_line(level, msg)

def sign_error(msg):
    level = 'error'
    message_line(level, msg)


time_s = time.time()
sign_info('START: {}'.format(time.strftime("%Y-%m-%d %H:%M:%S", time.localtime(time_s))))

origin_bin = sys.argv[1]
sign_bin = sys.argv[2]

# get bin size
bin_size = os.path.getsize(origin_bin)
sign_info('origin bin {input_bin} size: {size}'.format(input_bin=origin_bin,size=bin_size))


boot_struct_boot_hdr_size = 16
boot_struct_security = 2
boot_struct_reserved_012 = 2
boot_struct_key = 4+384+384
boot_struct_sig = 384
boot_struct_size = boot_struct_boot_hdr_size + boot_struct_security + boot_struct_reserved_012 + boot_struct_key+boot_struct_sig

code_sig_struct_code_size = 4
code_sig_struct_sig = 384
code_sig_struct_size = code_sig_struct_code_size + code_sig_struct_sig

bin_tail_size = 4
# code size use to gen hash
valid_content_size = bin_size - boot_struct_size - code_sig_struct_size - bin_tail_size
# transfer little byte order
valid_content_size_4B = valid_content_size.to_bytes(4,byteorder='little',signed=False)
sign_info('code size {codesize} hex:{valid_content_size_4B} '.format(codesize=valid_content_size,valid_content_size_4B=valid_content_size_4B.hex()))


# open sec bin as stream
bin_name_arry = origin_bin.split(".",2)
sec_bin = bin_name_arry[0]+"_sec.bin"
fd_sec = open(sec_bin,'wb+')

# open bin as stream
fd = open(origin_bin,'rb+')

# copy boot struct
sign_info('boot_struct_size {} '.format(boot_struct_size))
fd_sec.write(fd.read(boot_struct_size))
sign_info('fd tell {0} fd_sec tell {1}'.format(fd.tell(),fd_sec.tell()))

# write code sig struct
# write code size
fd_sec.write(valid_content_size_4B)
# write code sign
fd_sig = open(sign_bin,'rb+')
fd_sec.write(fd_sig.read(384))
fd_sig.close()

fd.seek(code_sig_struct_size,1)
sign_info('fd tell {0} fd_sec tell {1}'.format(fd.tell(),fd_sec.tell()))

# write others
sign_info('valid_content_size {0} '.format(valid_content_size))
left_content_size = valid_content_size
read_step_len = 1024*1024
while  left_content_size > read_step_len:
    tmp = fd.read(read_step_len)
    fd_sec.write(tmp)
    left_content_size -= read_step_len
    sign_info('fd tell {0} fd_sec tell {1}'.format(fd.tell(),fd_sec.tell()))

fd_sec.write(fd.read(left_content_size))

fd_sec.write(fd.read(4))

# sign_info('fd tell {0} fd_sec tell {1}'.format(fd.tell(),fd_sec.tell()))

fd_sec.close()
fd.close()

time_e = time.time()
sign_info('END: {}'.format(time.strftime("%Y-%m-%d %H:%M:%S", time.localtime(time_e))))
sign_info('SPEND TIME: {}s'.format(int(time_e)-int(time_s)))