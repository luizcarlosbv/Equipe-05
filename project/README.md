# Criando uma rede privada com IBFT 2.0 usando o Hyperledger Besu
## Criação da rede
* Para fins de teste, iniciamos criando 4 nós validadores locais que formam o início da rede.
```shell
project/  
├── Node-1  
│   ├── data  
├── Node-2  
│   ├── data  
├── Node-3  
│   ├── data  
└── Node-4  
    ├── data
```
* Criamos o bloco Genesis e adicionamos as chaves públicas e privadas a cada bloco
```shell
IBFT-Network/  
├── genesis.json  
├── Node-1  
│   ├── data  
│   │   ├── key  
│   │   ├── key.pub  
├── Node-2  
│   ├── data  
│   │   ├── key  
│   │   ├── key.pub  
├── Node-3  
│   ├── data  
│   │   ├── key  
│   │   ├── key.pub  
├── Node-4  
│   ├── data  
│   │   ├── key  
│   │   ├── key.pub
```
* Após a configuração inicial, podemos inicializar os nós da rede. O primeiro nó terá a função de Bootnode, o qual é utilizado para iniciar uma nova rede. O seguinte comando é utilizado dentro da pasta do Node-1 para fazer a inicialização:
```shell
besu --data-path=data --genesis-file=../genesis.json --rpc-http-enabled --rpc-http-api=ETH,NET,IBFT --host-allowlist="*" --rpc-http-cors-origins="all"
```
* Como resultado o **Node-1** é inicializado:
```shell
2023-07-17 01:58:47.193-03:00 | main | INFO  | Besu | Starting Besu
2023-07-17 01:58:47.467-03:00 | main | INFO  | Besu | jemalloc library not found, memory usage may be reduced by installing it
2023-07-17 01:58:47.509-03:00 | main | INFO  | Besu | 
####################################################################################################
#                                                                                                  #
# Besu version 23.4.4                                                                              #
#                                                                                                  #
# Configuration:                                                                                   #
# Network: Custom genesis file specified                                                           #
# Network Id: 1337                                                                                 #
# Data storage: Forest                                                                             #
# Sync mode: Full                                                                                  #
# RPC HTTP APIs: ETH,NET,IBFT                                                                      #
# RPC HTTP port: 8545                                                                              #
#                                                                                                  #
# Host:                                                                                            #
# Java: openjdk-java-20                                                                            #
# Maximum heap size: 3.83 GB                                                                       #
# OS: linux-x86_64                                                                                 #
# glibc: 2.35                                                                                      #
# Total memory: 15.32 GB                                                                           #
# CPU cores: 20                                                                                    #
#                                                                                                  #
####################################################################################################
[...]
2023-07-17 01:58:48.165-03:00 | main | INFO  | DefaultP2PNetwork | Enode URL enode://8d0ca7fb2cb8b939b887cb17303f0d99ec841826a1ef127e19503125c3d1f258beb3529732b91843573696eb1368c82c07aeb07ee7b2b72aa9679beb9274b94e@127.0.0.1:30303
```
* Após a inicialização do Bootnode (Node-1), como podemos ver anteriormente, é gerada a Enode URL, que será utilizada para inicializar os demais nós da rede:
* Inicialização e resultado **Node-2**
```shell
besu --data-path=data --genesis-file=../genesis.json --bootnodes=enode://8d0ca7fb2cb8b939b887cb17303f0d99ec841826a1ef127e19503125c3d1f258beb3529732b91843573696eb1368c82c07aeb07ee7b2b72aa9679beb9274b94e@127.0.0.1:30303 --p2p-port=30304 --rpc-http-enabled --rpc-http-api=ETH,NET,IBFT --host-allowlist="*" --rpc-http-cors-origins="all" --rpc-http-port=8546
```
```shell
2023-07-17 02:03:42.003-03:00 | main | INFO  | Besu | Starting Besu
2023-07-17 02:03:42.232-03:00 | main | INFO  | Besu | jemalloc library not found, memory usage may be reduced by installing it
2023-07-17 02:03:42.275-03:00 | main | INFO  | Besu | 
####################################################################################################
#                                                                                                  #
# Besu version 23.4.4                                                                              #
#                                                                                                  #
# Configuration:                                                                                   #
# Network: Custom genesis file specified                                                           #
# Network Id: 1337                                                                                 #
# Data storage: Forest                                                                             #
# Sync mode: Full                                                                                  #
# RPC HTTP APIs: ETH,NET,IBFT                                                                      #
# RPC HTTP port: 8546                                                                              #
#                                                                                                  #
# Host:                                                                                            #
# Java: openjdk-java-20                                                                            #
# Maximum heap size: 3.83 GB                                                                       #
# OS: linux-x86_64                                                                                 #
# glibc: 2.35                                                                                      #
# Total memory: 15.32 GB                                                                           #
# CPU cores: 20                                                                                    #
#                                                                                                  #
####################################################################################################
```
* O mesmo é feito com os demais, mudando apenas a porta que cada um escuta, por todos serem executados localmente.
* Ao final, para chegar se tudo está correto, podemos utilizar a **API** fornecida para verificar se a rede está funcionando da maneira correta. O resultado mostra que existem **4 nós** validadores conectados:
```shell
curl -X POST --data '{"jsonrpc":"2.0","method":"ibft_getValidatorsByBlockNumber","params":["latest"], "id":1}' localhost:8545
```
```shell
{
  "jsonrpc" : "2.0",
  "id" : 1,
  "result" : [ 	"0x05ab454bf329aea7ad5fda6547f9af2b8a043d83", 
				"0x19d556e7813b5506857788ece43359413f68240d",
				"0x38d05253baccbc428aed1a39ac1a77194619a9cd",
				"0xaa5c9371f9aa934981b8e06871eff14c2950eba6" ]
```

## Adição e remoção de nós

[Doing...]

