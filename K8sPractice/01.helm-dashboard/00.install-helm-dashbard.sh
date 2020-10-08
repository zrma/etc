helm repo add kubernetes-dashboard https://kubernetes.github.io/dashboard/
helm repo update
kubectl create ns kubernetes-dashboard
helm install kubernetes-dashboard kubernetes-dashboard/kubernetes-dashboard --set=service.externalPort=8888 --namespace kubernetes-dashboard
