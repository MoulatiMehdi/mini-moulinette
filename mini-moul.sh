#!/bin/bash

source ~/mini-moulinette/mini-moul/config.sh
# assignment name
assignment=$1
norm_error=0
FAIL="\033[1;97;101m FAIL ${DEFAULT}"
PASS="\033[1;30;102m PASS ${DEFAULT}"
run_norminette() {
  if command -v norminette &> /dev/null; then
    norminette -R CheckForbiddenSourceHeader ex*/*
  else
    echo "norminette not found, skipping norminette checks"
  fi
}

function handle_sigint {
  echo "${RED}Script aborted by user. Cleaning up..."
  rm -R ../mini-moul
  echo ""
  echo "${GREEN}Cleaning process done.${DEFAULT}"
  exit 1
}
check_normenette() {
  file="$1"
  result=$(run_norminette "$file")  # Assuming normenette_checker provides output like "Error: ex00/ft_print_program_name.c: error message"


    # Check if the result starts with "Error"
    if [[ "$(echo $result | sed -n '/Error!$/p' | tr '\n' ' ')" == *Error!* ]]; then
      echo -e "  ${FAIL} \033[1;34m $(dirname $file)/${DEAULT}$(basename $file)${DEFAULT}"  # Red crossmark (UTF-8 code)
      ((norm_error++))
      return 1  # Return non-zero to indicate error
    else
      echo -e "  ${PASS} \033[1;34m$(dirname $file)/${DEFAULT}$(basename $file)${DEFAULT}"  # Green checkmark (UTF-8 code)
      return 0  # Return non-zero to indicate error
    fi
  }
  # Function to determine if current directory matches a pattern
  detect_assignment() {
    [[ $1 =~ ^C(0[0-9]|1[0-3])$ ]]
  }

  if detect_assignment $1 ; then
    cp -R ~/mini-moulinette/mini-moul mini-moul
    trap handle_sigint SIGINT
    cd mini-moul
    ./test.sh "$assignment"
    rm -R ../mini-moul
    cd ..

    printf " ${GREEN}Check Norminette...\n\n"
    error=0

    find . \( -name "*.c" -o -name "*.h" \) -type f | while IFS= read -r file; do
    check_normenette "$file"
  done

  if [[ $norm_error -gt 0 ]]; then 
    printf "\n\033[1;37;101m FAIL ${DEFAULT} norminette\n"
    printf "\t${RED}Some files doesn't respect the norminette rules.${DEFAULT}\n"
    printf "\t${RED}Please make sure that the folder contains only files correspond to the exercices.${DEFAULT}\n\n"
  fi

else
  printf "${RED}Current directory does not match expected pattern (C[00~13]).${DEFAULT}\n"
  printf "${RED}Please navigate to an appropriate directory to run tests.${DEFAULT}\n"
  fi
  exit 1

