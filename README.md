strela
======

To install you do

    ZMQ_STRELA="<path to zmq_strela_dir>"
    $ZMQ_STRELA/scripts/install.sh

To run broker (first terminal)

    source $ZMQ_STRELA/scripts/env.sh
    zs_broker

Let's start few clients (second and third terminal)

    source $ZMQ_STRELA/scripts/env.sh
    zs_client

And let's send some message from worker (forth terminal)

    source $ZMQ_STRELA/scripts/env.sh
    zs_worker -m "My Message"

And now you should see in second and third terminal message "My Message"
