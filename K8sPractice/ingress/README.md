#### nginx ingress controller

https://kubernetes.github.io/ingress-nginx/deploy/

```bash
wget https://raw.githubusercontent.com/kubernetes/ingress-nginx/master/deploy/static/mandatory.yaml
```

* mandatory : nginx ingress controller infra deployment



#### Bare-metal ingress-nginx service

https://kubernetes.github.io/ingress-nginx/deploy/

```bash
wget https://raw.githubusercontent.com/kubernetes/ingress-nginx/master/deploy/static/provider/baremetal/service-nodeport.yaml
```

* service-nodeport : expose ingress to external


#### ingress

* nginx-ingress : simple ingress route example


nginx(deploy/app) <- nginx(svc) <- nginx-public(ingress/route) <- nginx-ingress-controller(deploy/infra) <- ingress-nginx(svc)
