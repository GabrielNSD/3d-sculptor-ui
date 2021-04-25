#ifndef SCULPTOR_H
#define SCULPTOR_H

#include "voxel.h"

/**
 * @brief A classe Sculptor implementa um desenhador tridimensional
 * com várias funções
 */

class Sculptor
{
protected:
    Voxel ***v;
    int nx;
    int ny;
    int nz;
    float r;
    float g;
    float b;
    float a;

public:
        /**
         * @brief
         *
         * Cria um espaço tridimensional de acordo com as dimensões fornecidas
         *
         * @param _nx dimensão do construtor no eixo x
         * @param _ny dimensão do construtor no eixo y
         * @param _nz dimensão do construtor no eixo z
         *
         * @details
         *
         * Antes da lista
         * <ul>
         *  <li> Teste</li>
         * </ul>
         *
         *
         */

    Sculptor(int _nx, int _ny, int _nz);

    /** @brief
         *
         * Destrutor padrão
         */
        ~Sculptor();

        /** @brief
         * Define uma cor, no formato rgba, para todos os Voxels que forem ativados após a invocação deste método
         *
         * @param r vermelho (valores de 0 a 255)
         * @param g verde (valores de 0 a 255)
         * @param b azul (valores de 0 a 255)
         * @param a transparência (valores de 0 a 1)
         *
         */

        void setColor(float r, float g, float b, float alpha);

        /** @brief
         *
         * Posiciona um Voxel no espaço, de acordo com as coordenadas fornecidas
         *
         * @param x coordenada do Voxel no eixo x
         * @param y coordenada do Voxel no eixo y
         * @param z coordenada do Voxel no eixo z
         */
        void putVoxel(int x, int y, int z);

        /** @brief
         *
         * Remove um Voxel do espaço, de acordo com as coordenadas fornecidas
         *
         * @param x coordenada do Voxel no eixo x
         * @param y coordenada do Voxel no eixo y
         * @param z coordenada do Voxel no eixo z
         */
        void cutVoxel(int x, int y, int z);

        /** @brief
         *
         * Cria uma caixa no espaço com dimensões x0 a x1, y0 a y1 e z0 a z1
         * Todos os Voxels dessa geometria possuem a mesma cor
         *
         *
         * @param x0 coordenada inicial da caixa no eixo x
         * @param x1 coordenada final da caixa no eixo x
         * @param y0 coordenada inicial da caixa no eixo y
         * @param y1 coordenada final da caixa no eixo y
         * @param z0 coordenada inicial da caixa no eixo z
         * @param z1 coordenada final da caixa no eixo z
         *
         *
         */
        void putBox(int x0, int x1, int y0, int y1, int z0, int z1);

        /** @brief
         *
         * Apaga uma caixa no espaço com dimensões x0 a x1, y0 a y1 e z0 a z1
         *
         *
         * @param x0 coordenada inicial da caixa no eixo x
         * @param x1 coordenada final da caixa no eixo x
         * @param y0 coordenada inicial da caixa no eixo y
         * @param y1 coordenada final da caixa no eixo y
         * @param z0 coordenada inicial da caixa no eixo z
         * @param z1 coordenada final da caixa no eixo z
         *
         *
         */
        void cutBox(int x0, int x1, int y0, int y1, int z0, int z1);

        /** @brief
         *
         * Cria uma esfera no espaço
         *
         * @param xcenter coordenada do centro da esfera no eixo x
         * @param ycenter coordenada do centro da esfera no eixo y
         * @param zcenter coordenada do centro da esfera no eixo z
         * @param radius raio da esfera
         *
         */
        void putSphere(int xcenter, int ycenter, int zcenter, int radius);

        /** @brief
         *
         * Apaga um volume esférico no espaço
         *
         * @param xcenter coordenada do centro da esfera no eixo x
         * @param ycenter coordenada do centro da esfera no eixo y
         * @param zcenter coordenada do centro da esfera no eixo z
         * @param radius raio da esfera
         *
         */
        void cutSphere(int xcenter, int ycenter, int zcenter, int radius);

        /** @brief
         *
         * Cria um elipsóide no espaço
         *
         * @param xcenter coordenada do centro do elipsóide no eixo x
         * @param ycenter coordenada do centro do elipsóide no eixo y
         * @param zcenter coordenada do centro do elipsóide no eixo z
         * @param rx maior distância entre o centro do elipsóide e extremidade da forma geométrica, no eixo x
         * @param ry maior distância entre o centro do elipsóide e extremidade da forma geométrica, no eixo y
         * @param rz maior distância entre o centro do elipsóide e extremidade da forma geométrica, no eixo y
         *
         */
        void putEllipsoid(int xcenter, int ycenter, int zcenter, int rx, int ry, int rz);

        /** @brief
         *
         * Apaga o volume de um elipsóide no espaço
         *
         * @param xcenter coordenada do centro do elipsóide no eixo x
         * @param ycenter coordenada do centro do elipsóide no eixo y
         * @param zcenter coordenada do centro do elipsóide no eixo z
         * @param rx maior distância entre o centro do elipsóide e extremidade da forma geométrica, no eixo x
         * @param ry maior distância entre o centro do elipsóide e extremidade da forma geométrica, no eixo y
         * @param rz maior distância entre o centro do elipsóide e extremidade da forma geométrica, no eixo y
         *
         */
        void cutEllipsoid(int xcenter, int ycenter, int zcenter, int rx, int ry, int rz);

        /** @brief
         *
         * Cria um arquivo .off que permite a visualização das formas em um software apropriado
         *
         * @param filename nome do arquivo de destino
         */
        void writeOFF(char *filename);
};

#endif // SCULPTOR_H
