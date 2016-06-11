
/**
 * Escreva a descrição da classe ParNVendasNCliDif aqui.
 * 
 * @author (seu nome) 
 * @version (número de versão ou data)
 */
public class ParNVendasNCliDif
{
    // variáveis de instância - substitua o exemplo abaixo pelo seu próprio
    private int vendas;
    private int diferentes;


    public ParNVendasNCliDif()
    {
        this.vendas = 0;
        this.diferentes=0;
    }

    
    public ParNVendasNCliDif(int vendas, int diferentes)
    {
        this.vendas = vendas;
        this.diferentes=diferentes;
    }
    
    
    
    public ParNVendasNCliDif(ParNVendasNCliDif p)
    {
        vendas = p.getVendas();
        diferentes=p.getDiferentes();

    }
    
    
    public int getVendas(){
        return this.vendas;
    }
    
    public int getDiferentes(){
        return this.diferentes;
    }
    
    
    
    public void setDiferentes(int d){
        this.diferentes=d;
    }
    
    
    
    public void setVendas(int vendas){
        this.vendas=vendas;
    }
    
    
    public ParNVendasNCliDif clone(){
        return new ParNVendasNCliDif(this);
    }
    
    
    public boolean equals(Object o){
        if (this==o) return true;
        if(this.getClass().equals(o.getClass())){
            ParNVendasNCliDif aux = (ParNVendasNCliDif) o;
            return (aux.getVendas()==this.getVendas() && aux.getDiferentes()==(this.getDiferentes()));
        }
        return false;
    }
}
