#!/bin/bash

# useage
# -t target-name -g gen-header-tool -n sign-tool -s 5 -a 0x12345678 -i file -o file -r rot-pri-key-pem -p user-pub-key-bin -m user-pri-key-pem

while [[ $# -gt 0 ]]; do
  case $1 in
    -t|--target)
      TARGET_NAME="$2"
      shift # past argument
      shift # past value
      ;;
    -g|--gen-header-tool)
      GEN_HEADER_FILE="$2"
      shift # past argument
      shift # past value
      ;;
    -n|--sign-tool)
      SIGN_TOOL_FILE="$2"
      shift # past argument
      shift # past value
      ;;
    -s|--header-version)
      HEADER_VERSION="$2"
      shift # past argument
      shift # past value
      ;;
    -a|--load-addr)
      LOAD_ADDR="$2"
      shift # past argument
      shift # past value
      ;;
    -i|--input)
      INPUT_FILE="$2"
      shift # past argument
      shift # past value
      ;;
    -o|--output)
      OUTPUT_FILE="$2"
      shift # past argument
      shift # past value
      ;;
    -r|--rot-pri-key-pem)
      ROT_PRI_KEY_FILE="$2"
      shift # past argument
      shift # past value
      ;;
    -p|--user-pub-key-bin)
      USER_PUB_KEY_FILE="$2"
      shift # past argument
      shift # past value
      ;;
    -m|--user-pri-key-pem)
      USER_PRI_KEY_FILE="$2"
      shift # past argument
      shift # past value
      ;;
    *)
      echo "Unknown option $1"
      exit 1
      ;;
  esac
done

# step 1: add a preset header to the bin file
$GEN_HEADER_FILE -s $HEADER_VERSION -a $LOAD_ADDR -i $INPUT_FILE -o $OUTPUT_FILE

# make a copy for step 1
cp $OUTPUT_FILE $OUTPUT_FILE.pre

# step 2: generate the boot struct file
OUTPUT_DIR=$(dirname $OUTPUT_FILE)
$SIGN_TOOL_FILE --root --boot-struct $ROT_PRI_KEY_FILE 0 0 0 $USER_PUB_KEY_FILE $OUTPUT_DIR/${TARGET_NAME}_boot_struct.bin

# step 3: sign the code data and update the boot struct data in the image file
$SIGN_TOOL_FILE --root $USER_PRI_KEY_FILE $OUTPUT_DIR/${TARGET_NAME}_boot_struct.bin $OUTPUT_FILE

