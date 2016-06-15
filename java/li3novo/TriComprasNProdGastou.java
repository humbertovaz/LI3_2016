
import java.io.Serializable;


/**
 * Escreva a descrição da classe TriComprasNProdGastou aqui.
 * 
 * @author (seu nome) 
 * @version (número de versão ou data)
 */
public class TriComprasNProdGastou implements Serializable
{
    // variáveis de instância - substitua o exemplo abaixo pelo seu próprio
   private int vendas;
   private int diferentes;
   private double gastou;


    public TriComprasNProdGastou()
    {
        this.vendas = 0;
        this.diferentes=0;
        this.gastou=0;
    }

    
    public TriComprasNProdGastou(int vendas, int diferentes, double g)
    {
        this.vendas = vendas;
        this.diferentes=diferentes;
        this.gastou=g;
    }
    
    
    
    public TriComprasNProdGastou(TriComprasNProdGastou p)
    {
        this.vendas = p.getVendas();
        this.diferentes=p.getDiferentes();
        this.gastou=p.getGastou();
    }
    
    
    public double getGastou(){
        return this.gastou;
    }
    
    public int getVendas(){
        return this.vendas;
    }
    
    public int getDiferentes(){
        return this.diferentes;
    }
    
    public void setGastou(double g){
        this.gastou=g;
    }
    
    public void setDiferentes(int d){
        this.diferentes=d;
    }
    
    
    
    public void setVendas(int vendas){
        this.vendas=vendas;
    }
    
    
    public TriComprasNProdGastou clone(){
        return new TriComprasNProdGastou(this);
    }
    
    
    public boolean equals(Object o){
        if (this==o) return true;
        if(this.getClass().equals(o.getClass())){
            TriComprasNProdGastou aux = (TriComprasNProdGastou) o;
            return (aux.getVendas()==this.getVendas() && aux.getDiferentes()==(this.getDiferentes()) && aux.getGastou()==this.getGastou());
        }
        return false;
    }
}
