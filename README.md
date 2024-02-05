# Patisserie
## PoC Project on Recipes / pastries Management

### Description:
The purpose of this project is to provide a simple interface (a CLI for instance), to manage pastries orders according to what pastries and recipes are available in the "database". 

This is a very first step and it was originally made for me to get familiar with C++ features such as POO & containers, and I had fun !

### Getting Started guide:
1) First clone the project locally :
```console
toto@toto: git clone -b master https://github.com/GuiQuad06/patisserie.git
```
2) Build the project:
```console
toto@toto: cd patisserie
toto@toto: mkdir build
toto@toto: cd build
toto@toto: cmake ..
toto@toto: cmake --build .
toto@toto: ./patisserie
```
You will have to create those empty files to make it works:
- recettes.txt
- patisseries.txt
- commandes.txt

Create these files either at project source path or in any other path at condition you specify it as a command line argument :
```console
toto@toto: ./patisserie ~/my_database_files/
```

### Procedure:
When you enter the application, you will be asked to enter:
1) A Recipe:
- Follow the Form to create a Recipe by composing it with an ingredients map {Ingredient name, Quantity}.
2) A Pastry:
- Follow the Form to create a Pastry by composing it with a Recette map {Recette, Quantity} based on what is available in recettes.txt database.  
3) An Order:
- Follow the Form to create a Commande by composing it with a Patisserie map {Patisserie, Nb of People} based on what is available in patisseries.txt database.
4) Generate a Shoppingh List: (Not Implemented Yet)
   
5) Remove a Recipe: (Not Implemented Yet)
    
6) Remove a Pastry: (Not Implemented Yet)
    
7) Remove an Order: (Not Implemented Yet)
    
