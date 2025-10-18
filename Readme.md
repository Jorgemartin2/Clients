# 🧾 Projeto de Gerenciamento de Clientes

Sistema simples para **cadastro, edição, visualização e exclusão de clientes**, com salvamento automático dos dados em arquivo `.txt`.

## 💡 Descrição

O programa armazena informações como **nome, CPF, data de nascimento, endereço, sexo e telefone**, exibindo os clientes em ordem alfabética.  
Os dados são salvos em arquivo de texto, garantindo persistência entre execuções.

## 🧠 Compatibilidade

O sistema detecta automaticamente o sistema operacional:
- **Windows:** cria a pasta `Client` e o arquivo `clientes.txt` no disco `C:`  
- **Linux:** cria o arquivo em `/tmp/clientes.txt`

## ▶️ Como Executar

```bash
gcc main.c -o clientes
./clientes
```

## 🖥️ Requisitos

- Compilador **C** (GCC, MinGW ou equivalente)  
- Sistema Operacional: **Windows** ou **Linux**

## 👤 Autor

Desenvolvido por **Jorge Martin**