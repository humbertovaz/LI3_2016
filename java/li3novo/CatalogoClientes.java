 

import java.util.HashSet;
import java.util.Set;


/**
 *
 * 
 */
public class CatalogoClientes {
    
  private Set<String> catalogoClientes;

    public CatalogoClientes() {
        this.catalogoClientes = new HashSet<>();
    }

    public CatalogoClientes(HashSet<String> catalogoClientes) {
        this.catalogoClientes = new HashSet<>();
        
        for (String c: catalogoClientes)
            this.catalogoClientes.add(c);
    }

    public CatalogoClientes(CatalogoClientes c) {
        this.catalogoClientes = c.getCatalogoClientes();
    }

    private Set<String> getCatalogoClientes() {
        Set<String> res = new HashSet<>();
        
        if (this.catalogoClientes != null)
            for (String c: catalogoClientes) 
                res.add(c);
        
        return res;
    }

    private void setCatalogoClientes(Set<String> catalogoClientes) {
        Set<String> tmp = new HashSet<>();
        
        for (String c: catalogoClientes){
            tmp.add(c);
        }
        
        this.catalogoClientes=tmp;
        
        
    }
    
    @Override
    public boolean equals(Object obj) {
        if (this == obj)
            return true;
        
        if ((obj == null) || (this.getClass() != obj.getClass()))
            return false;
        
        CatalogoClientes c = (CatalogoClientes) obj;
        return (this.catalogoClientes.equals(c.getCatalogoClientes()));
    }

    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder();
        
        sb.append("Catálogo: ").append("\n");
        
        for(String c :this.catalogoClientes) {
        
            
            sb.append(c).append("\n");
           
        }
        return sb.toString();
    }
    
    @Override
    public CatalogoClientes clone() {
        return new CatalogoClientes(this);
    }
    
    /**
     * Insere um cliente no Catálogo de Clientes.
     * @param cliente
     */
    public void insere(String cliente) {
        this.catalogoClientes.add(cliente);
    }
    
    /**
     * Verifica se um dado cliente existe no Catálogo de Clientes.
     * @param cliente
     * @return true se o cliente existir, false caso contrário
     */
    public boolean existe(String cliente) {
        return this.catalogoClientes.contains(cliente);
    }
    
    /**
     * Devolve o número de clientes que estão no Catálogo de Clientes.
     * @return número de clientes
     */
    public int getTotalClientes() {
        return this.catalogoClientes.size();
    }
}
