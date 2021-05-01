# SO2-notes
 Apontamentos e notas das aulas de SO2

## Compilar

O projecto é de cmake, para lo correr basta fazer isto:
```powershell
mkdir build
cd build
# irá gerar os projectos de VS
cmake ..
# podem abrir com o vs o projecto ou simplesmente compilar com
msbuild
```
Relembro que é preciso ter o cmake instalado e no path para poder correr o cmake, e o msbuild pode obter com a opção de command line tools no vs installer ou com o standalone build tools para windows, para terem as build tools da microsoft no cmd/powershell tem de executar o atalho development console no startar.

Para aqueles que estão em ssh podem simplesmente correr:
```cmd
%comspec% /k "C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\vcvars64.bat"
```
isto caso a estejam com a mesma versão do vs que eu.

Também é possivel usar o cmake no vs se checarem essa box no vs installer.

## Desenvolver com o vscode

Se quizerem desenvolver sem o vs podem usar o vscode.

As extensões que eu uso são:
 - **C/C++** da **Microsoft**
 - **Cmake** do **twxs**
 - **Cmake Tools** da **Microsoft**
 - **Visual Studio IntelliCode** da **Microsoft**
 - **Output Colorizer** da **IBM**


### Linux bros
Para quem está em Linux pode deixar a vm a correr no background e usar o vscode nativo, instalem o **Remote Development** da **Microsoft** e façam ssh na vossa vm, se quizerem mais sobre o assunto venham ler o [Linux-subsystem-for-windows-Cross-Compilation](https://github.com/OnikenX/Linux-subsystem-for-windows-Cross-Compilation).


### Fichas minimamente feitas

- [x] Ficha 1
- [x] Ficha 2
- [x] Ficha 3
- [ ] Ficha 4
- [ ] Ficha 5
