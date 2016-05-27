#!/bin/bash

failed=0
binary_dir=${1:-bin}

function verify() {
  # returns ret indicating whether the test succeeded or failed
  ret=0
  local name=${1#.*_}
  local log_out=/tmp/out_operators_unit.log
  echo -e "Test '${name%Debug}' \c"
  "$1" > "$log_out"
  grep -q 'All tests passed' "$log_out" && echo "succeeded."
  if [ ! $? -eq 0 ] ; then
    echo "failed!"
    ret=1    
  fi
}

for test in ./"$binary_dir"/test_* ; do
  verify $test
  if [ $ret -eq 1 ] ; then
    ((failed++))
  fi
done

if [ $failed -ge 1 ] ; then
  echo "# of failed tests:" $failed && exit 1
fi
