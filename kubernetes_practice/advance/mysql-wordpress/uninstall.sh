kubectl delete secret mysql-pass
kubectl delete -f volumes.yaml
kubectl delete -f mysql-deployment.yaml
kubectl delete -f wordpress-deployment.yaml
