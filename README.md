# TN741-HPC
Para alguns exemplos é necessário baixar e compilar a biblioteca do [PAPI] (https://icl.utk.edu/papi/)
Atenção que para permitir a leitura dos eventos, é necessário alterar um parâmetro do kernel linux
como usuário root:

`sh -c "echo 2 > /proc/sys/kernel/perf_event_paranoid"`
