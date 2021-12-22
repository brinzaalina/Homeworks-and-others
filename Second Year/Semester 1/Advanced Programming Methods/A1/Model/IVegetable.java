/*
5. Intr-o sera se cultiva rosii, ardei si vinete.
Sa se afiseze toate legumele cu greutatea mai mare
de 0.2 kg.
 */
package Model;

public interface IVegetable {
    float getWeight();
    void setWeight(float weight);
    String toText();
}
