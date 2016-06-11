 
import java.util.*;
import java.util.stream.*;


public class Faturacao {
    private int totalVendas;
    private double totalFaturado;
    private HashMap<Produto, InfoProduto> produtosVendidos;
    
    public Faturacao(){
        this.totalVendas=0;
        this.totalFaturado=0;
        this.produtosVendidos=new HashMap<>();
    
    }
    public Faturacao(Faturacao faturacao){
        this.totalVendas=faturacao.getTotalVendas();
        this.totalFaturado=faturacao.getTotalFaturado();
        this.produtosVendidos=(HashMap<Produto, InfoProduto>) faturacao.getProdutosVendidos();
    }
    public Faturacao(int totalVendas, double totalFaturado, HashMap<Produto,InfoProduto> produtosVendidos) {
        this.totalVendas = totalVendas;
        this.totalFaturado = totalFaturado;
        this.produtosVendidos=new HashMap<>();
        produtosVendidos.forEach((k,v)->this.produtosVendidos.put(k,v));
    }
    
    
    public int getTotalVendas() {
        return totalVendas;
    }

    public double getTotalFaturado() {
        return totalFaturado;
    }

    
    private int add(int t, int v){
        t+=v;
        return t;
    }
    
    public int getTotalVendasMes(int mes){
        return this.produtosVendidos.values().stream().mapToInt(i-> i.getVendasMes(mes)).sum();
    }
    
    public Map<Produto,InfoProduto> getProdutosVendidos() {
        TreeMap<Produto,InfoProduto> tmp = new TreeMap<>();
        for(Map.Entry<Produto, InfoProduto> entry : produtosVendidos.entrySet()){
            tmp.put(entry.getKey().clone(), entry.getValue().clone());
        }
        return tmp;
    }
    public void setTotalVendas(int totalVendas) {
        this.totalVendas = totalVendas;
    }

    public void setTotalFaturado(double totalFaturado) {
        this.totalFaturado = totalFaturado;
    }

    public void setProdutosVendidos(TreeMap<Produto,InfoProduto> produtosVendidos) {
        this.produtosVendidos.clear();
        produtosVendidos.forEach((k,v)-> this.produtosVendidos.put(k,v));
    }
    
    private void listAdd(List<Produto> l, Produto p, InfoProduto i){
        if (!(i.comprado())){
            l.add(p.clone());
        }
    }
    
    public List<Produto> getNaoVendidos(){
        List<Produto> res = new ArrayList<>();
        this.produtosVendidos.forEach((k,v)->listAdd(res,k,v));
        return res.stream().sorted((e1,e2)->e1.getCodigoProduto().compareTo(e2.getCodigoProduto())).collect(Collectors.toList());
    }
    
    
    
    
    
    
    
    
    
    public void inserProduto(Produto p) {
    
       this.produtosVendidos.put(p, new InfoProduto());
    
    
    }
    
   public void inser(int mes,int filial,double faturado,int quantidade,Produto p) {
        this.totalVendas++;
        this.totalFaturado=quantidade*faturado;
        
       
        
            this.produtosVendidos.get(p).inser(mes, filial, faturado, quantidade);
        
        
        
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
        final Faturacao other = (Faturacao) obj;
        if (this.totalVendas != other.getTotalVendas()) {
            return false;
        }
        if (Double.doubleToLongBits(this.totalFaturado) != Double.doubleToLongBits(other.getTotalFaturado())) {
            return false;
        }
        if (!Objects.equals(this.produtosVendidos, other.getProdutosVendidos())) {
            return false;
        }
        return true;
    }

    @Override
    public String toString() {
        return "Faturacao{" + "totalVendas=" + totalVendas + ", totalFaturado=" + totalFaturado + ", produtosVendidos=" + produtosVendidos + '}';
    }
    
    @Override
    public Faturacao clone() {
        return new Faturacao(this);
    }
    
    
    
}
