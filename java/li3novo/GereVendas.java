

import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.FileReader;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.util.ArrayList;
import java.util.*;
import java.util.Set;

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 *
 * @author gil
 */
public class GereVendas  {
      private static final String ficheiroObej="C:\\Users\\gil\\Documents\\GitHub\\LI3-Parte-java\\data\\hipermercado.dat";
     private static final String path ="C:\\Users\\gil\\Documents\\GitHub\\LI3-Parte-java\\data\\";
     private static Menu menuMain, menuCarregar, menuEstatistica, menuInterativo,menuEstatistica1;
     private static String fichCompras;
     private static final String ficheiroClientes="C:\\Users\\gil\\Documents\\GitHub\\LI3-Parte-java\\data\\Clientes.txt";
     private static final String ficheiroProdutos="C:\\Users\\gil\\Documents\\GitHub\\LI3-Parte-java\\data\\Produtos.txt";
     private static String ultimo;
     
     
    /**
     * @param args the command line arguments
     * @throws java.io.IOException
     */
    public static void main(String[] args) throws IOException {
        Hipermercado t=null;
        List<String> tmp;
        List<Venda>tmp1;
        String linha,ficheiro;
        String s;
        int top;
        Produto produto ;
        Cliente cliente;
        int flag;
        carregaMenu();
        clear();
        System.out.print("\nPara poder executar o programa GereVendas tem de efetuar um primeiro carregamento dos dados.\n");
        System.out.println("\nDeseja carregar o ultimo estado do programa? Caso contario, os ficheiros sao carregados (S/N)  ");
        linha=Input.lerString();
        if(linha.charAt(0)=='S' || linha.charAt(0)=='s') {
            System.out.print("\nDeseja introduzir o nome do ficheiro a carregar? (S/N)  ");
            linha = Input.lerString();
            if ((linha.charAt(0) == 'S') || (linha.charAt(0) == 's')) {
                System.out.print("Introduza o nome do ficheiro a carregar sem a extensao .dat: ");
                linha = Input.lerString();
                ficheiro = GereVendas.path + linha + ".dat";
                System.out.print("\n");
                GereVendas.ultimo=ficheiro;
            } else {
                ficheiro = GereVendas.ficheiroObej;
                GereVendas.ultimo=ficheiro;
                System.out.println("\nCarregamento default do ficheiro...");
            }
            System.out.print("A proceder ao carregamento do ficheiro ");
            System.out.print(ficheiro);
            System.out.println("...");
            try {
                Crono.start();
                ObjectInputStream ois = new ObjectInputStream(new FileInputStream(ficheiro));    
                t = (Hipermercado) ois.readObject();
                Crono.stop();
                System.out.println("Ficheiro carregado com sucesso! ("+Crono.print()+" s)");
                ois.close();
                flag=3;
               } 
            catch (IOException | ClassCastException | ClassNotFoundException e) {
                System.out.println(e.getMessage());
                flag=1;
            }
        } 
        else {
            flag=2;
        }
        if(flag==2 || flag==1) {
            t=new Hipermercado();
            System.out.println("\nCarregamento default dos ficheiros...");
                    Crono.start();
                    tmp=carregaCatalgoProduto();
                    for(String a : tmp) {
                        produto = new Produto(a);
                        t.inserCatalogoProdutos(produto);
                        t.inserProdutoFaturacao(produto);
                        
                    }
                    tmp.clear();
                    tmp=carregaCatalgoClientes();
                    for(String a :tmp){
                        cliente = new Cliente(a);
                        t.inserCatalogoClientes(cliente);
                        t.inserClienteFilial(cliente);
                       
                    }
                    carregaFicheiros();
                    tmp1=carregaCompras();
                    for(Venda a:tmp1) {
                      
                        produto = new Produto(a.getCodigoProduto());
                        cliente = new Cliente(a.getCodigoCliente());
                        t.inserVendas(a.getFilial(),cliente,produto,a.getQuantidade(),a.getPreco(),a.getMes(), a.getModoDeCompra());
                    }
                    Crono.stop();
            System.out.println("Ficheiros carregados com sucesso! ("+Crono.print()+" s)");
            System.out.println(t.getVendasErradas());
        }
        waitMenu();
        do{
            clear();
            GereVendas.menuMain.executa();
            switch(menuMain.getOpcao()) {
                case 1:
                    clear();
                    System.out.println("\nDeseja carregar o ultimo estado do programa? "+ "Caso contario, o ficheiro defualt e carregado (S/N)  ");
                    linha=Input.lerString();
                    if(linha.charAt(0)=='S' || linha.charAt(0)=='s') {
                        System.out.print("\nDeseja introduzir o nome do ficheiro a carregar? (S/N)  ");
                        linha = Input.lerString();
                        if ((linha.charAt(0) == 'S') || (linha.charAt(0) == 's')) {
                            System.out.print("Introduza o nome do ficheiro a carregar sem "+ "a extensao .dat: ");
                            linha = Input.lerString();
                            ficheiro = GereVendas.path + linha + ".dat";
                            GereVendas.ultimo=ficheiro;
                            System.out.print("\n");
                        } 
                        else {
                            ficheiro = GereVendas.ficheiroObej;
                            GereVendas.ultimo=ficheiro;
                            System.out.println("\nCarregamento default do ficheiro...");
                        }
                        System.out.print("A proceder ao carregamento do ficheiro ");
                        System.out.print(ficheiro);
                        System.out.println("...");
                        try {
                            Crono.start();
                            System.out.println("A carregar o ficheiro" + ficheiro);
                            ObjectInputStream ois = new ObjectInputStream(new FileInputStream(ficheiro));    
                            t = (Hipermercado) ois.readObject();
                            Crono.stop();
                            System.out.println("Ficheiro carregado com sucesso! ("+Crono.print()+" s)");
                            ois.close();
                            flag=3;
                        } catch (IOException | ClassCastException | ClassNotFoundException e) {
                            System.out.println(e.getMessage());
                            flag=1;
                        }
                    } 
                    else {
                        flag=2;
            
                    }
       
                    if(flag==2 || flag==1) {
                        t=new Hipermercado();
                        System.out.println("\nCarregamento default dos ficheiros...");
                        Crono.start();
                        tmp=carregaCatalgoProduto();
                        for(String a : tmp) {
                      
                        produto = new Produto(a);
                        t.inserCatalogoProdutos(produto);
                        t.inserProdutoFaturacao(produto);
                        
                        }
                        tmp.clear();
                        tmp=carregaCatalgoClientes();
                        for(String a :tmp) {
                            cliente = new Cliente(a);
                        t.inserCatalogoClientes(cliente);
                        t.inserClienteFilial(cliente);
                        }
                        carregaFicheiros();
                        tmp1=carregaCompras();
                        for(Venda a:tmp1) {
                        produto = new Produto(a.getCodigoProduto());
                        cliente = new Cliente(a.getCodigoCliente());
                        t.inserVendas(a.getFilial(),cliente,produto,a.getQuantidade(),a.getPreco(),a.getMes(), a.getModoDeCompra());
                        }
                        Crono.stop();
                        System.out.println("Ficheiros carregados com sucesso! ("+Crono.print()+" s)");
                    }
                    waitMenu();
                    break;  
                case 2:
                    clear();
                    System.out.print("Deseja inserir um nome ao ficheiro que quer gravar? (S/N) ");
                    linha =Input.lerString();
                    if (((linha.charAt(0)) == 'S') || ((linha.charAt(0)) == 's')) {
                        System.out.print("Introduza o nome do ficheiro: ");
                        linha = Input.lerString();
                        ficheiro = GereVendas.path + linha + ".dat";
                    } else {
                        ficheiro  = GereVendas.ficheiroObej;
            
                    }
                    System.out.println("\nA gravar os dados no ficheiro "+ficheiro +"...");
        
                    try{
                        Crono.start();
                        FileOutputStream carrega=new  FileOutputStream(ficheiro);
                        ObjectOutputStream oos = new ObjectOutputStream(carrega);
                        oos.writeObject(t);
                        oos.flush();
                        oos.close();
                        Crono.stop();
                        System.out.println("Ficheiro guardado com sucesso " + Crono.print() );
                    }
                    catch(IOException ex){
                        System.out.println(ex.getMessage());
            
                    }
                    waitMenu();
                    break;
                case 3:
                    clear();
                    do {
                        clear();
                        menuEstatistica.executa();
                        switch (menuEstatistica.getOpcao()) {
                            case 1:
                                clear();
                                int aux1,aux2,aux3,aux4;
                               Crono.start();
                                aux1=t.getProdutos().getTotalProdutos();
                                aux2=t.produtosDiferentes();
                                aux3=t.getCatalogo().getTotalClientes();
                                aux4=t.clientesDiferens();

                                System.out.println("*************************************************************");          
                                System.out.println("Ultimo ficheiro lido : " +GereVendas.ultimo);
                                System.out.println("Vendas erradas : "+t.getVendasErradas());
                                System.out.println("Total dos produtos lidos : "+aux1);
                                System.out.println("Total dos produtos comprados : "+aux2);
                                System.out.println("Total dos produtos nao comprados : "+(aux1-aux2));
                                System.out.println("Total de clientes lidos : "+aux3);
                                System.out.println("Total de clientes que compraram : "+aux4);
                                System.out.println("Total de clientes que nada compraram : "+(aux3-aux4));
                                System.out.println("Total de compras com o valor zero : "+t.getComprasNulas());
                                System.out.println("Faturacao total : "+t.getFaturacaoGlobal());
                                Crono.stop();
                                System.out.println("Tempo : "+Crono.print());    
                                System.out.println("*************************************************************");    
                                waitMenu();
                               
                                break;
                            case 2:
                                do{ 
                                    clear();
                                    GereVendas.menuEstatistica1.executa();
                                    switch(GereVendas.menuEstatistica1.getOpcao()){
                            
                            
                                        case 1:/*
                                        int[] td =t.getNumCompras();
                                        clear();
                                        int i;
                                        Crono.start();
                                        System.out.println("*************************************************************");
                                        for(i=0;i<12;i++) {
                                            System.out.println("No mes " +(i+1) +" efectuou-se " +td[i] +" compras");

                                        }
                                        Crono.stop();
                                        System.out.println("Tempo " +Crono.print());
                                        System.out.println("*************************************************************");
                                        waitMenu();
                                        */
                                       break;
                        
                             
                                       case 2:
                                       /*
                                        * int j;
                                        * double soma=0.0;
                                        * clear();
                                        * Crono.start();
                                        * double [][] dp =t.getFacturacaoMes();
                                        * System.out.println("*************************************************************");
                                        * for(i=0;i<12;i++) {
                                
                                        for(j=0;j<3;j++) {
                                            
                                        System.out.println("Faturacao no mes "+(i+1)+" na filial "+ 
                                            (j+1)+" e " + dp[i][j] );
                                        soma+=dp[i][j];
                                        }
                                        
                                
                                    }
                                    System.out.println("Total em todas as filiais " +soma);
                                
                                
                                    System.out.println("Tempo " +Crono.print());
                                    System.out.println("*************************************************************");
                                    waitMenu();
                                    */
                                   break;
                                
                                
                        case 3:/*
                                 clear();
                                 Crono.start();
                                 int []d = t.getNrDistintos();
                                  System.out.println("*************************************************************");
                             for(i=0;i<12;i++) {

                                 
                                System.out.println("O numero de clientes que compraram no mes "+
                                        (i+1)+" foram  "+d[i]);
                                } 
                                Crono.stop();
                                System.out.println("Tempo " +Crono.print());
                                 System.out.println("*************************************************************");
                                waitMenu();
                            */
                        break;
                        
                        }
                        
                        }while(GereVendas.menuEstatistica1.getOpcao()!=0);
                        
                       
                        break;
                        
                        
                        
                        }
                         
        } while (menuEstatistica.getOpcao() != 0);
                
                break;
           
                
                
               
            case 4:
                do
                {clear();
                
                GereVendas.menuInterativo.executa();
                
                
                switch(GereVendas.menuInterativo.getOpcao()) {
                
                    case 1:
                        clear();
                        Crono.start();
                        List<Produto> lista = t.produtosNaoVendidos();
                        Crono.stop();
                        imprimeLista(lista,Crono.stop());
                        
                        waitMenu();
                        
                    break;
                    
                    case 2:
                        clear();
                        int mes = mesUtilizador();
                        Crono.start();
                        ParNVendasNCliDif p=t.vendasRealizadasMes(mes);
                        int total=p.getVendas();
                        int nclientes=p.getDiferentes();
                        Crono.stop();
                        System.out.println("Vendas: " + total+ "\n Clientes: " + nclientes +"\n Tempo : " +Crono.print());
                        
                        waitMenu();
                    break;
                    
                    case 3:
                        clear();
                        s = codigo();
                        cliente=new Cliente(s);
                       Crono.start();
                        if(t.existeCliente(cliente)){
                             
                            TriComprasNProdGastou[] res=t.clienteCompras(new Cliente(s));
                            Crono.stop();
                            System.out.println("Tempo : "+ Crono.print());
                            System.out.println("Mes\tCompras\tProdutos\tGastou");
                            for(int i=0;i<12;i++){
                                if(i<10){
                                    System.out.println("0"+(i+1)+"\t"+ res[i].getVendas()+"\t"+res[i].getDiferentes()+"\t"+res[i].getGastou());
                                }
                                else{
                                    System.out.println((i+1)+"\t"+ res[i].getVendas()+"\t"+res[i].getDiferentes()+"\t"+res[i].getGastou());
                                }
                            }
                        }
                        else{
                            System.out.println("Cliente inexistente");
                        }
                        
                        
                        waitMenu();
                        
                    break;
                    
                    case 4:
                        clear();
                       String codigo=codigo();
                       Crono.start();
                        if(t.existeProduto(codigo)){
                            TriComprasNProdGastou[] res=t.produtoComprado(new Produto(codigo));
                            Crono.stop();
                            System.out.println("Tempo : "+Crono.print());
                            System.out.println("Mes\tCompras\tClientes\tFaturado");
                            for(int i=0;i<12;i++){
                                if(i<10){
                                    System.out.println("0"+(i+1)+"\t"+ res[i].getVendas()+"\t"+res[i].getDiferentes()+"\t"+res[i].getGastou());
                                }
                                else{
                                    System.out.println((i+1)+"\t"+ res[i].getVendas()+"\t"+res[i].getDiferentes()+"\t"+res[i].getGastou());
                                }
                            }
                        }
                        else{
                            System.out.println("Produto inexistente");
                        }
                        waitMenu();
                    break; 
                    
                    case 5:
                        clear();
                        s= codigo();
                        cliente=new Cliente(s);
                        if(t.existeCliente(cliente)){
                            Crono.start();
                            List<ParProdutoQuantidade> res = t.getCompradosCliente(new Cliente(s));
                            Crono.stop();
                            imprimeListaPar(res,Crono.stop());
                        }
                        else{
                            System.out.println("Cliente inexistente");
                        }
                        waitMenu();
                    break;
                    
                    case 6:
                        clear();
                        top = lerInt();
                        Crono.start();
                        if(top>0){
                            List<ParProdutoQuantidade> res = t.getTopXVendidos(top);
                            imprimeListaPar(res,Crono.stop());
                            
                        }
                        else{
                            System.out.println("Numero invalido");
                        }
                        waitMenu();
                        
                    break;
                    
                    case 7:
                        clear();
                        Crono.start();
                        for(int i=1;i<4;i++){
                            List<Cliente> res = t.top3Filial(i);
                            Crono.stop();
                            System.out.println("Filial: "+i);
                            for(int j=0;j<3;j++)System.out.println(res.get(j));
                            
                        }
                        System.out.println("Tempo : "+Crono.stop());
                        waitMenu();
                    break;
                    
                    
                    
                    case 8:
                        clear();
                        top = lerInt();
                        Crono.start();
                        if(top>0){
                            List<ParClienteNDif> res = t.compraramMaisDiferentes(top);
                            Crono.stop();
                            imprimeListaParCliente(res,Crono.stop());
                            
                        }
                        else{
                            System.out.println("Numero invalido");
                        }
                        waitMenu();
                        
                    break;
                    
                    
                    
                    case 9:
                        clear();
                        s = codigo();
                        top =lerInt();
                        if(top>0){
                            Crono.start();
                            List<ParClienteQuantidade> res = t.getTopXBuyers(new Produto(s),top);
                            Crono.stop();
                            imprimeListaParClienteQuantidade(res,Crono.stop());
                            
                        }
                        else{
                            System.out.println("Numero invalido");
                        }
                         waitMenu();
                    break;
                    
                    
                    
                    
                    
                
                
                }
                
                
                
                
                
                }while(GereVendas.menuInterativo.getOpcao()!=0);
                
                
                
                
                
                
                
                
                
                
                
                break;
        
        
        
            }
     
        
        }
        while(GereVendas.menuMain.getOpcao()!=0);
    
    }
   
    private static int lerInt() {
    
        int mes;
        
        do{
            System.out.println("Introduza um numero maior que zero");
            mes=Input.lerInt();
    
        } while(mes<=0);
    
    
        return mes;
    
    }
    
    private static String codigo() {
     
        String codigo;
        System.out.println("Introduza um codigo");
            codigo=Input.lerString();
    return codigo;
    
    }
    
    private static int mesUtilizador(){
        int mes;
        
        do{
            System.out.println("Introduza um mês de 1-12");
            mes=Input.lerInt();
    
        } while(mes<=0&& mes>12);
    
    
        return mes;
    }
    
   
    private static void query1(Set<String> lista,double tempo){
         List<String> res;
        String linha,string;
        int max=lista.size();
        char opcao='q';
        int pag=1;
        int j,i=0;
        string="";
         res = new ArrayList<>(lista);
         int tamanho=lista.size();
        if(max!=0) {
        
            while(opcao!='s') {
            
                clear();
                System.out.println(string);
                System.out.print("Produtos nao comprados     Paginas: ");
                System.out.print(pag);
                System.out.print(" / ");
                System.out.print((int) Math.ceil(((double) max) / 20));
                System.out.print("\t\t(");
                System.out.print(tempo);
                System.out.println(" s)  "+ "Total nao comprados "+ tamanho +"\n");
                
                
               for (j = 0; j < 20 && (i + j) != max; j++) {
                    System.out.println(res.get(i + j));
                }
               
               i += j;
                System.out.print("\n* * * * * * * * * * * * *\n*   Introduza opcao:\t*\n*   'a' para avancar\t*\n*   'r' para recuar\t*\n*   's' para sair\t*\n* * * * * * * * * * * * *\n-opcao: ");
                opcao = Input.lerString().charAt(0);
                if (opcao == 'a') {
                    if (i == max) {
                        i -= j;
                        string = "\nNao pode avancar mais!\n";
                    } else {
                        pag++;
                        string = "\nAvancou!\n";
                    }
                } else {
                    if (opcao == 'r') {
                        if (i <= 20) {
                            i -= j;
                            string = "\nNao pode recuar mais!\n";
                        } else {
                            pag--;
                            i = i - j - 20;
                            string = "\nRecuou!\n";
                        }
                    } else {
                        i -= j;
                        string = "\nopcao Invalida!\n";
                    }
                }
              
            }

        }
        
        
        else {
        
            System.out.println("\nTodos os produtos foram comprados!");
           
            waitMenu();
        }
    
    }
    
    
    private static void query2(int cliente,int vendas,double tempo) {
        clear();
        System.out.println("**********************************************************");
        System.out.println("Tempo : ( " + tempo + " s )");
        System.out.println("Numero de clientes que realizaram compras foi : " + cliente);
        System.out.println("Numero de vendas realizadas : " + vendas);
        System.out.println("**********************************************************");
      waitMenu();
    }
    
    
    
    
    private static void carregaMenu() {
    
         String[] menu1 = {"Carregar programa",
            "Gravar Estado do Programa",
            "Consultas Estataticas",
            "Consultas Interativas"};
        String[] menu2 = {"Carregar Ficheiros",
            "Carregar ultimo Estado do Programa"};
        String[] menu3 = {"Dados do ultimo Ficheiro de Compras Lido",
            "Dados Gerais do Programa"};
        
        String[] menu4 = {
          "Lista alfabetica dos produtos nunca comprados",
          "Numero total de vendas e clientes de um dado mes",
          "Determinar o numero de compras, produtos e total gasto de um dado cliente em cada mes",
          "Numero de compras,quantos clientes diferentes o compraram e o total vendido"
                + "em cada mes para um determinado produto",
          "Lista dos produtos que um cliente mais comprou e o seu total",
          "Os N produtos mais vendidos e os numero de clientes distintos que os compraram",
          "3 maiores compradores",
          "Os N clientes que mais compraram produtos diferentes",
          "Os N clientes que mais compraram um determinado produto e o valor gasto"
         };
        String [] menu5 = {"Numero total de compras por mes",
            "Faturacao total por mes para cada filial e o global",
            "Numero de clientes que compraram em cada mes"
        };
    menuMain = new Menu(menu1);
    menuCarregar = new Menu(menu2);
    menuEstatistica = new Menu(menu3);
    menuInterativo = new Menu(menu4);
    menuEstatistica1=new Menu(menu5);
    
    }
    
   
    
    
    /**
     * Server para que o menu não desapareca
     */
    private static void waitMenu() {
        
        System.out.println("\nPressiona qualquer tecla para continuar...");
        Input.lerString();
    }

    /**
     * Este metodo imprime 50 vezes uma linha vazia, em que no fim desta linha
     * ap automaticamente colocado um '\n'. Isto serve para que seja mais facil
     * a leitura por exemplo de um menu, em que assim so aparece o menu com o
     * qual estamos efetivamente a interagir.
     */
    private static void clear() {
        for (int i = 0; i < 50; i++) {
            System.out.println();
        }
    }
    
  
    
    
    /**
     * Carrega os ficheiros de texto
     */
    private static void carregaFicheiros() throws IOException {
        
        String input;

        System.out.print("\nDeseja introduzir o nome do ficheiro Compras a carregar? (S/N)  ");
        input=Input.lerString();
        if ((input.charAt(0) == 'S') || (input.charAt(0) == 's')) {
            System.out.println("\nIntroduza o nome do ficheiro Compras a carregar: ");
            System.out.println("Exemplo : Vendas_1M");
            input =Input.lerString();

            if (input.equals("Vendas_1M") || input.equals("Vendas_3M") || input.equals("Vendas_5M"))
            {
                GereVendas.fichCompras = GereVendas.path+input + ".txt";
                GereVendas.ultimo=GereVendas.fichCompras;
                System.out.println("A proceder a leitura do ficheiro \n"+GereVendas.fichCompras);
                System.out.println("");
            } else {
                GereVendas.fichCompras = GereVendas.path+"Vendas_1M.txt";
                GereVendas.ultimo=GereVendas.fichCompras;
                 System.out.println("\nA ler o ficheiro "+GereVendas.fichCompras);
                System.out.println("\nCarregamento default dos ficheiros...");
            }
        } else {
            GereVendas.fichCompras = GereVendas.path+"Vendas_1M.txt";
            GereVendas.ultimo=GereVendas.fichCompras;
            System.out.println("\nA ler o ficheiro "+GereVendas.fichCompras);
            System.out.println("\nCarregamento default dos ficheiros...");
        }
        
    }
    
     
    
   
    private static List<Venda> carregaCompras() throws FileNotFoundException, IOException{
    String linha;
        Venda a;
        Scanner scanFile = null ;
        ArrayList vendas = new ArrayList<>();
       scanFile = new Scanner (new FileReader(GereVendas.fichCompras));
       scanFile.useDelimiter(System.getProperty("line.separator"));
        while(scanFile.hasNext()) {
            
            a=parseLinhaVenda(scanFile.nextLine());
            vendas.add(a.clone());
        }
        if (scanFile!=null) scanFile.close();
        
            return vendas;
    }
    
    /*
     0 e o codigo produto
    1 e o preco
    2 e a quantidade 
    3 modo de compra
    4 codigo cliente
    5 mes 
    6 filial
    */
    private static Venda parseLinhaVenda(String linha){
    linha=linha.trim(); // tira espaços (antes e depois)
    String [ ] tmp=linha.split(" ");
    String s=tmp[3];
   Venda venda;
       venda = new Venda(tmp[0],tmp[4],s.charAt(0),Integer.parseInt(tmp[5]),
                 Integer.parseInt(tmp[6]),Double.parseDouble(tmp[1]),Integer.parseInt(tmp[2]));
   return venda;
}
            
         
  static private void imprimeLista(List<Produto> l,double tempo){
      int i,j,pags,lpag,op,exitf=1;
      Input in= new Input();
      pags=l.size()/10;
      lpag=l.size()%10;
      if(lpag!=0) pags++;
      if(l.size()==0){
          System.out.print('\u000C');
          System.out.println("Sem resultados");
      }
      for(i=0;i<pags && exitf!=0;){
          System.out.print('\u000C');
          System.out.println("Pagina " + (i+1) + "de " + pags);
          System.out.println("Tempo:  " + tempo);
          for(j=i*10;j<i*10+10 && j<l.size();j++){
              System.out.println(l.get(j).toString());
          }
          System.out.println("1 - Proxima pagina. \t 2 - Pagina anterior. \t 0 - Sair");
          op=in.lerInt();
          switch(op){
              case 0: exitf=0;
                      break;
              case 1: if(i<pags){
                        i++;
                      }
                      break;
              case 2: if(i>0){
                        i--;
                      }
                      break;
            }
        }  
  }
  
  static private void imprimeListaPar(List<ParProdutoQuantidade> l,double tempo){
      int i,j,pags,lpag,op,exitf=1;
      Input in= new Input();
      pags=l.size()/10;
      lpag=l.size()%10;
      if(lpag!=0) pags++;
      if(l.size()==0){
          System.out.print('\u000C');
          System.out.println("Sem resultados");
      }
      for(i=0;i<pags && exitf!=0;){
          System.out.print('\u000C');
          System.out.println("Tempo : " + tempo);
          System.out.println("Pagina " + (i+1) + "de " + pags);
          for(j=i*10;j<i*10+10 && j<l.size();j++){
              System.out.println("Codigos\tQuantidade");
              System.out.println(l.get(j).getProduto().toString()+"\t"+l.get(j).getQuantidade());
          }
          System.out.println("1 - Proxima pagina. \t 2 - Pagina anterior. \t 0 - Sair");
          op=in.lerInt();
          switch(op){
              case 0: exitf=0;
                      break;
              case 1: if(i<pags){
                        i++;
                      }
                      break;
              case 2: if(i>0){
                        i--;
                      }
                      break;
            }
        }  
  }
   
  
  static private void imprimeListaParCliente(List<ParClienteNDif> l,double tempo){
      int i,j,pags,lpag,op,exitf=1;
      Input in= new Input();
      pags=l.size()/10;
      lpag=l.size()%10;
      if(lpag!=0) pags++;
      if(l.size()==0){
          System.out.print('\u000C');
          System.out.println("Sem resultados");
      }
      for(i=0;i<pags && exitf!=0;){
          System.out.print('\u000C');
          System.out.println("Tempo : "+tempo);
          System.out.println("Pagina " + (i+1) + "de " + pags);
          for(j=i*10;j<i*10+10 && j<l.size();j++){
              System.out.println("Codigos\tQuantidade");
              System.out.println(l.get(j).getCliente().toString()+"\t"+l.get(j).getDiferentes());
          }
          System.out.println("1 - Proxima pagina. \t 2 - Pagina anterior. \t 0 - Sair");
          op=in.lerInt();
          switch(op){
              case 0: exitf=0;
                      break;
              case 1: if(i<pags){
                        i++;
                      }
                      break;
              case 2: if(i>0){
                        i--;
                      }
                      break;
            }
        }  
  }
  
  
  static private void imprimeListaParClienteQuantidade(List<ParClienteQuantidade> l,double tempo){
      int i,j,pags,lpag,op,exitf=1;
      Input in= new Input();
      pags=l.size()/10;
      lpag=l.size()%10;
      if(lpag!=0) pags++;
      if(l.size()==0){
          System.out.print('\u000C');
          System.out.println("Sem resultados");
      }
      for(i=0;i<pags && exitf!=0;){
          System.out.print('\u000C');
          System.out.println("Tempo : " +tempo);
          System.out.println("Pagina " + (i+1) + "de " + pags);
          for(j=i*10;j<i*10+10 && j<l.size();j++){
              System.out.println("Codigos\tQuantidade\tGasto");
              System.out.println(l.get(j).getCliente().toString()+"\t"+l.get(j).getQuantidade()+"\t"+l.get(j).getGasto());
          }
          System.out.println("1 - Proxima pagina. \t 2 - Pagina anterior. \t 0 - Sair");
          op=in.lerInt();
          switch(op){
              case 0: exitf=0;
                      break;
              case 1: if(i<pags){
                        i++;
                      }
                      break;
              case 2: if(i>0){
                        i--;
                      }
                      break;
            }
        }  
  }
  
  
  
    /*
        carregar os produtos e os clientes
   */
   private static List<String> carregaCatalgoProduto() throws FileNotFoundException, IOException {
    Scanner scanFile = null ;
        String line;
        ArrayList<String> tmp= new ArrayList<>();
        scanFile = new Scanner (new FileReader(GereVendas.ficheiroProdutos));
        scanFile.useDelimiter(System.getProperty("line.separator"));
        
        System.out.printf("A proceder a leitura do ficheiro %s...\n", GereVendas.ficheiroProdutos);
        
        while (scanFile.hasNext()) {
           tmp.add(scanFile.nextLine());
        }
         if (scanFile!=null) scanFile.close();
         
    return tmp;
   }
   
   private static List<String>carregaCatalgoClientes() throws FileNotFoundException, IOException {
       Scanner scanFile = null ;
       String line;
       ArrayList<String> tmp= new ArrayList<>();
       System.out.println("A proceder a leitura do ficheiro..."+GereVendas.ficheiroClientes);
       scanFile = new Scanner (new FileReader((GereVendas.ficheiroClientes)));
       scanFile.useDelimiter(System.getProperty("line.separator"));
        while (scanFile.hasNext()) {
           tmp.add(scanFile.nextLine());
        }
         if (scanFile!=null) scanFile.close();
         
       return tmp;
   } 
   
   
   
   
   
    
}