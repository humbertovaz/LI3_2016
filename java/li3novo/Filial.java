 
import java.io.Serializable;
import java.util.*;
import java.util.stream.Collectors;
/**
 *
 *
 */
public class Filial implements Serializable{
    private Map<Cliente,InfoCliente> informacaoClientes; // // está correto



    public Filial( Map<Cliente, InfoCliente> informacaoClientes) {
        this.informacaoClientes= new HashMap<>();
        for (Map.Entry<Cliente, InfoCliente> entry : informacaoClientes.entrySet()){
            this.informacaoClientes.put(entry.getKey().clone(), (InfoCliente) entry.getValue().clone());
        }     
    }
    public Filial() {
        this.informacaoClientes=new TreeMap<>();
    }
    public Filial (Filial f){
        this.informacaoClientes=f.getInformacaoClientes();
    }
    public Map<Cliente,InfoCliente> getInformacaoClientes (){
        TreeMap<Cliente,InfoCliente> tmp= new TreeMap<>();
        this.informacaoClientes.forEach((k,v)->tmp.put(k.clone(),v.clone()));
        return tmp;
    }
    
    
    
    public Set<Cliente> getClientesCompraramProdutoMes(Produto p, int mes){
        Set<Cliente> res = new HashSet<>();
        this.informacaoClientes.entrySet().stream().filter(e -> e.getValue().produtoCompradoMes(p,mes)).map(e-> res.add(e.getKey().clone()));
        return res;
    }
    
    public Set<Cliente> getClientesCompraramProduto(Produto p){
        Set<Cliente> res = this.getClientesCompraramProdutoMes(p,1);
        for(int i=2;i<13;i++){
            Set<Cliente> aux = this.getClientesCompraramProdutoMes(p,i);
            aux.stream().map(e->res.add(e.clone()));
        }
        return res;
    
    }
    
    private void addListP(List<Cliente> l, Cliente c, InfoCliente i, Produto p){
        if(i.comprou(p)){
            l.add(c);
        }
    }
    
    private int compareDouble(double d,double d2){
        Double obj1 = new Double(d);
        Double obj2 = new Double(d2);
        return obj2.compareTo(obj1);
    }
    
    public List<Cliente> getTop3Buyers(){
        List<Cliente> res=new ArrayList<>();
        informacaoClientes.entrySet().stream()
        .sorted((e1,e2)->compareDouble(e1.getValue().getTotalGasto(),e2.getValue().getTotalGasto())) 
        .limit(3) 
        .forEach(e->res.add(e.getKey().clone()));
        return res;
    }
    
    public double getGastouMes(Cliente c, int mes)
    {
        if (this.informacaoClientes.containsKey(c)){
            InfoCliente aux=this.informacaoClientes.get(c);
            return aux.getGastouMes(mes);
            
        }
        else return 0;
    }
    
    private void addListM(List<Cliente> l, Cliente c, InfoCliente i){
        int total=0;
        for(int j=0;j<12;j++){
            total+=i.getVendasMes(j);
        }
        if(total>0) l.add(c);
    }
    public List<Cliente> comprouMes(int i){
        List<Cliente> res = new ArrayList<>();
        this.informacaoClientes.forEach((k,v)->addListM(res,k,v));
        return res;
    }
    
    
    public Set<Cliente> compraramMes(int mes){
        Set<Cliente> res = new HashSet<>();
        this.informacaoClientes.entrySet().stream().filter(e -> e.getValue().comprouMes(mes)).map(e -> res.add(e.getKey().clone()));
        return res;
    }
    

    public Map<Cliente,ParClienteQuantidade> compraramProduto(Produto p){
        Map<Cliente,ParClienteQuantidade> res= new HashMap<>();
        this.informacaoClientes.forEach((k,v)-> addCliQuant(res,v,k,p));
        return res;
    }

    
    public double faturadoProdutoMes(Produto p, int mes){
        double res=0;
        for(InfoCliente i: this.informacaoClientes.values()){
            res+=i.getFaturadoProdutoMes(p,mes);
        }
        return res;
    }
    
    private void addCliQuant(Map<Cliente,ParClienteQuantidade> m, InfoCliente i, Cliente c, Produto p){
        if(i.comprou(p)){
            if(m.containsKey(c)){
                ParClienteQuantidade aux = m.get(c);
                aux.setQuantidade(aux.getQuantidade()+i.getQuantidadeProduto(p));
                aux.setGasto(aux.getGasto()+i.getGastouProduto(p));
            }
            else{
                ParClienteQuantidade aux = new ParClienteQuantidade(c,i.getQuantidadeProduto(p),i.getGastouProduto(p));
                m.put(c.clone(),aux);
            }
        }
    }
    

    
    public Set<Produto> getProdutosCompradosMes(Cliente c, int mes){
        Set<Produto> res = new HashSet<>();
        if(this.informacaoClientes.containsKey(c)){
            res=this.informacaoClientes.get(c).produtosCompradosMes(mes);
        }
        return res;
    }
    
    public int getVendasClienteMes(Cliente c, int mes){
        if(this.informacaoClientes.containsKey(c)){
            return this.informacaoClientes.get(c).getVendasMes(mes);
        }
        return 0;
    }
    
    public int getTotalVendasMes(int mes){
        int res=0;
        for(InfoCliente i: this.informacaoClientes.values()){
            res+=i.getVendasMes(mes-1);
        }
        return res;
    }
    
    public Map<Cliente, Set<Produto>> getListProd(){
        Map<Cliente,Set<Produto>> res = new HashMap<>();
        this.informacaoClientes.forEach((k,v)->res.put(k,v.getProds()));
        return res;
    }

    public Set<Cliente> getClienteCompraram() {
    Set<Cliente> tmp = new HashSet<>();
    
            for(Cliente a : this.informacaoClientes.keySet()) {
                tmp.add(a);
            
            }
    
    
    
    return tmp;
    }


    public Filial clone(){
        return new Filial(this);
    }

    
    
    public void inserClienteFilial(Cliente p) {
        this.informacaoClientes.put(p, new InfoCliente());
    }
    
    
    public int getQuantidadeComprada(Cliente c, Produto p){
        if(this.informacaoClientes.containsKey(c)){
            return this.informacaoClientes.get(c).getQuantidadeProduto(p);
        }
        return 0;
    }
    
    public Map<Produto,ParProdutoQuantidade> getComprados(Cliente c){
        Set<Produto> produtos = getProdutosCompradosMes(c,1);
        Map<Produto,ParProdutoQuantidade> res = new HashMap<>();
        for(int i=1;i<12;i++){
            Set<Produto> aux = getProdutosCompradosMes(c,i);
            aux.stream().map(e->produtos.add(e.clone()));
            aux.clear();
        }
        produtos.stream().map(e->res.put(e.clone(),new ParProdutoQuantidade(e.clone(),this.getQuantidadeComprada(c,e))));
        return res;
    }
    
    
    public void inserFilial(Cliente c , Produto p, int quantidade,double faturado,int mes,char modo) {
        this.informacaoClientes.get(c).inser(p, quantidade, faturado, mes, modo);
       
    }
    
    
    
    

    @Override
    public boolean equals(Object obj) {
        if (this == obj) {
            return true;
        }
        if (obj == null) {
            return false;
        }
        if (getClass() != obj.getClass()) {
            return false;
        }
        final Filial other = (Filial) obj;
        if (!Objects.equals(this.informacaoClientes, other.getInformacaoClientes())) {
            return false;
        }
        return true;
    }
    
     public int [] nrTotalComprasMes(){
    int i=0;
    int [] aux= nrTotalComprasMesNormal();
    int [] aux2=nrTotalComprasMesPromo();
    for (i=0;i<12;i++);
        aux[i]+=aux2[i];
    return aux;    
    }
   
    public int [] nrTotalComprasMesPromo(){
    int [] total = new int[12];
    int i;
    for (i=0;i<12;i++)
    for (InfoCliente ic : informacaoClientes.values()){
        for(InfoProdutoCliente ipc: ic.getProdutosComprados('P').values())
                total[i]+=ipc.getComprasMes(i);
        }  
    return total;
    }
   
   
    public int [] nrTotalComprasMesNormal(){
    int [] total = new int[12];
    int i;
    for (i=0;i<12;i++)
    for (InfoCliente ic : informacaoClientes.values()){
        for(InfoProdutoCliente ipc: ic.getProdutosComprados('N').values())
                total[i]+=ipc.getComprasMes(i);
        }  
    return total;
    }
    
     public double [] faturacaoFilial(){
        double [] total= new double [12];
        for(int i=0;i<12;i++){
            total[i]=faturacaoFilialMes(i);
        }
        return total;
    }
   
    private double faturacaoFilialMes(int mes){
        double fat=0;
        for(InfoCliente ic: informacaoClientes.values()){
            fat+=ic.getGastouMes(mes);
        }
        return fat;  
        }
    
    
    public int [] nrClientesQCompraram(){
    int [] nrClientes = new int [12];
        for(int i=0;i<12;i++)
            nrClientes[i]=nrClientesQCompraramMes(i);
    return nrClientes;
    }
   
    private int  nrClientesQCompraramMes(int mes){
        Set<InfoCliente> clientes = new HashSet<>();
            for(InfoCliente ic : informacaoClientes.values()){
                if(ic.getVendasMes(mes)>0)
                    clientes.add(ic.clone());
            }
    return clientes.size();
    }
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
}
