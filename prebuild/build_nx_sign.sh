
#!/bin/bash

DIR=$(cd $(dirname $0); pwd)
build_chip=$1

output=rtos/nuttx
if [ $# -eq 2 ]; then
    output=$2
fi

# Check if a directory exists
if [ ! -d "$output" ]; then
    echo "no such folder: $DIR"
    exit 1
fi

for file in "$output"/nuttx_*.bin; do
    [ -e "$file" ] || continue
    ./prebuild/security/bes_sign_tool/best_sign_v5_static --otp ./prebuild/security/bes_sign_tool/rsa_private_key.pem $file
    echo "sign $file done!!!"
done

cp ./prebuild/security/bes_sign_tool/pub_otp.bin $output
