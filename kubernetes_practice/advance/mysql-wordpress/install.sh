kubectl create secret generic mysql-pass --from-file=password.txt
kubectl create -f volumes.yaml
kubectl create -f mysql-deployment.yaml
kubectl create -f wordpress-deployment.yaml
