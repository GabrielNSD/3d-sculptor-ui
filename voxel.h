#ifndef VOXEL_H
#define VOXEL_H

/** @brief
 *
 * A estrutura Voxel permite que um cubo seja criado com sua propriedade de cor e transparência
 *
 *
 */

typedef struct{
    float r,g,b,a; //Colors (r,g,b) and transparency (a)
    bool isOn;
} Voxel;

#endif // VOXEL_H
