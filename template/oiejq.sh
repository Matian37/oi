#!/bin/bash


MEM_LIMIT="2097152"

if [ $# -lt 1 ]; then
    echo "Usage: $0 <program_to_test> [args...]"
fi

SELF="$(readlink -f "$0")"
SELF_DIR="$(dirname "$SELF")"

if [ -n "$MEM_LIMIT" ]; then
  MEASURE_MEM=1
fi

OPTS=""

if [ -z "$MEASURE_MEM" ]; then
  OPTS+=" --seccomp off"
  OPTS+=" --ptrace off"
fi

OPTS+=" --mount-namespace off"
OPTS+=" --pid-namespace off"
OPTS+=" --uts-namespace off"
OPTS+=" --ipc-namespace off"
OPTS+=" --net-namespace off"
OPTS+=" --capability-drop off --user-namespace off"
OPTS+=" -s"

if [ -n "$MEM_LIMIT" ]; then
    OPTS+=" -m $MEM_LIMIT"
fi

TMPFILE="$(mktemp)"

"$SELF_DIR/sio2jail" -f 3 -o oiaug $OPTS -- "$@" 3>"$TMPFILE"

read STATUS CODE TIME NVM MEM SYSC <"$TMPFILE"

exec >&2

echo ""
echo "-------------------------"

echo "$STATUS ${TIME}ms $(expr $(expr $MEM + 1023) / 1024)MB"

echo "EXITCODE: ${CODE}"

if [ "$STATUS" != "OK" ]; then
    echo "Details:"
    tail -n+2 "$TMPFILE"
fi

echo "-------------------------"


rm "$TMPFILE"
