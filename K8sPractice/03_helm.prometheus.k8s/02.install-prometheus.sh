helm install prometheus prometheus-community/prometheus \
  --namespace monitor \
  --set alertmanager.persistentVolume.enabled=false \
  --set server.persistentVolume.enabled=false \
  --set pushgateway.persistentVolume.enabled=false
