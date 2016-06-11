
 

import java.util.HashSet;
import java.util.Set;




/**
 *
 * 
 */
public class CatalogoProdutos {
    
    private Set<Produto> catalogoProdutos;

    public CatalogoProdutos() {
        this.catalogoProdutos = new HashSet<>();
    }

    public CatalogoProdutos(HashSet<Produto> catalogoProdutos) {
        this.catalogoProdutos = new HashSet<>();
        for (Produto p: catalogoProdutos){
            this.catalogoProdutos.add(p);
        }
    }

    public CatalogoProdutos(CatalogoProdutos c) {
        this.catalogoProdutos = c.getCatalogoProdutos();
    }

    private Set<Produto> getCatalogoProdutos() {
        Set<Produto> res = new HashSet<>();
        for (Produto p: catalogoProdutos){
            res.add(p);
        }
        return res;
    }

    private void setCatalogoProdutos(Set<Produto> catalogoProdutos) {
        Set<Produto> res = new HashSet<>();
        for (Produto p: catalogoProdutos){
            res.add(p);
        }
        this.catalogoProdutos=res;
    }
    
    @Override
    public boolean equals(Object obj) {
        if (this == obj){
            return true;
        }
        if ((obj == null) || (this.getClass() != obj.getClass())){
            return false;
        }
        CatalogoProdutos c = (CatalogoProdutos) obj;
        return (this.catalogoProdutos.equals(c.getCatalogoProdutos()));
    }

    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder();
        sb.append("Catálogo:").append("\n");
        for(Produto p:this.catalogoProdutos) {
            sb.append(p).append("\n");
        }
        return sb.toString();
    }
    
    @Override
    public CatalogoProdutos clone() {
        return new CatalogoProdutos(this);
    }
    
    /**
     * Insere um produto no Catálogo de Produtos
     * @param p 
     */
    public void insere(Produto p) {
        this.catalogoProdutos.add(p);
    }
    
    /**
     * Verifica se um produto existe no Catálogo de Produtos.
     * @param p
     * @return true se o cliente existir, false caso contrário
     */
    public boolean existe(Produto p) {
        return this.catalogoProdutos.contains(p);
    }
    
    /**
     * Devolve o número de produtos que estão no Catálogo de Produtos.
     * @return número de produtos
     */
    public int getTotalProdutos() {
        return this.catalogoProdutos.size();
    }
}

