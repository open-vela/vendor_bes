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
    return '[GEN HASH {}] {}'.format(level.upper(), msg)

def message_line(level, msg):
    for line in msg.splitlines():
        sys.stdout.write(message(level, line))
        sys.stdout.flush()


def hash_info(msg):
    level = 'info'
    message_line(level, msg)


def hash_warning(msg):
    level = 'warning'
    message_line(level, msg)

def hash_error(msg):
    level = 'error'
    message_line(level, msg)




time_s = time.time()
hash_info('SHA256 START: {}'.format(time.strftime("%Y-%m-%d %H:%M:%S", time.localtime(time_s))))

origin_bin = sys.argv[1]
# get bin size
bin_size = os.path.getsize(origin_bin)
hash_info('origin bin {input_bin} size: {size}'.format(input_bin=origin_bin,size=bin_size))


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

# open bin as stream
fd = open(origin_bin,'rb+')

# skip boot struct
fd.seek(boot_struct_size,0)
# skip code sig struct
fd.seek(code_sig_struct_size,1)

hash_info('cur offset: {offset} '.format(offset=fd.tell()))

valid_content = fd.read(valid_content_size)

hash_info('after read valid_content cur offset: {offset} '.format(offset=fd.tell()))

# hash_info('cur offset: \n{valid_content}'.format(valid_content=valid_content.hex()))
hash = hashlib.sha256(valid_content)
hash_info('bin_hash: {}'.format(hash.hexdigest()))
hash_info('bin_hash: {}'.format(hash.digest()))


bin_name_arry = origin_bin.split(".",2)
hash_bin = bin_name_arry[0]+"_hash.bin"
# open hash bin write
fd_hash = open(hash_bin,'wb+')
fd_hash.write(hash.digest())
fd_hash.close()
hash_info('hash_bin: {}'.format(hash_bin))

fd.close()

time_e = time.time()
hash_info('SHA256 END: {}'.format(time.strftime("%Y-%m-%d %H:%M:%S", time.localtime(time_e))))
hash_info('SPEND TIME: {}s'.format(int(time_e)-int(time_s)))


