#!/bin/sh
echo "-------------------------------------------------------------------------------"
echo "run the command below."
echo ""
echo "while true; do wget -q -O- http://nginx.ingress-example.svc.cluster.local; done"
echo "-------------------------------------------------------------------------------"

kubectl run -it --rm --generator=run-pod/v1 loadgen --image=busybox -n ingress-example /bin/sh
