# https://kubernetes.github.io/ingress-nginx/deploy/

## watch status
```bash
kubectl --namespace ingress-nginx get services -o wide -w ingress-nginx-controller
```

## check version
```bash
POD_NAME=$(kubectl get pods -n ingress-nginx -l app.kubernetes.io/name=ingress-nginx -o jsonpath='{.items[0].metadata.name}')
kubectl exec -n ingress-nginx -it $POD_NAME -- /nginx-ingress-controller --version
```
