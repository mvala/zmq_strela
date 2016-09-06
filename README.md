=======
mvala zaciatok

mucha OK

strela
======

To install you do

    ZMQ_STRELA="<path to zmq_strela_dir>"
    $ZMQ_STRELA/scripts/install.sh

To run broker (first terminal)

    source $ZMQ_STRELA/scripts/env.sh
    zs_broker -w tcp://*:5555 -c tcp://*:5556

Let's start few clients (second and third terminal)

    source $ZMQ_STRELA/scripts/env.sh
    zs_client -b tcp://localhost:5556

And let's send some message from worker (forth terminal)

    source $ZMQ_STRELA/scripts/env.sh
    zs_worker -b tcp://localhost:5555 -m "My Message"

And now you should see in second and third terminal message "My Message"

Test
