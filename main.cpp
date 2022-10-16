#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include "noise.h"
#include "mymap.h"
#include <chrono>

namespace glo
{
    int width{600};
    int heigth{600};
    int hw{width / 2};
    int hh{heigth / 2};

    double incr{1.0};
    double rot{};
    double myPi{6.283184};
    sf::Vector2f startCoords;
    sf::Vector2f endCoords;
    int colRandR{};
    int colRandG{};
    int colRandB{};
    double mClick{};
}

// ---------- MAIN ----------
// ---------- MAIN ----------
int main()
{

    int hw{glo::width / 2};
    int hh{glo::heigth / 2};

    srand(time(0));

    sf::RenderWindow window(sf::VideoMode(glo::width, glo::heigth), "Noise Test");

    window.setFramerateLimit(60);

    while (window.isOpen())
    {

        sf::Event event;
        while (window.pollEvent(event))
        {

            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed)
                if (event.mouseButton.button == sf::Mouse::Left)
                    glo::mClick = 30;
            if (event.type == sf::Event::MouseButtonReleased)
                if (event.mouseButton.button == sf::Mouse::Left)
                    glo::mClick = 0;
        }

        window.setActive();
        window.clear();

        // ---------- START ----------
        sf::VertexArray lines(sf::LineStrip);
        int count{1};
        for (double a = 0; a < glo::myPi; a += 0.1)
        {
            double noiseValue{mymap(IntegerNoise(glo::incr / 2), -1.0, 1.0, 120.0, 128.0 + glo::mClick)};
            glo::incr++;
            glo::colRandR = rand() % 230 + 20;
            glo::colRandG = rand() % 230 + 20;
            glo::colRandB = rand() % 230 + 20;
            double r{noiseValue};
            double x{r * cos(a + glo::rot)};
            double y{r * sin(a + glo::rot)};

            sf::Vertex point(sf::Vector2f(glo::hw + x, glo::hh + y), sf::Color(glo::colRandR, glo::colRandG, glo::colRandB));

            if (count == 1)
            {

                glo::startCoords = sf::Vector2f(glo::hw + x, glo::hh + y);
            }
            count++;
            if (count == 64)
            {
                glo::endCoords = sf::Vector2f(glo::hw + x, glo::hh + y);
            }

            lines.append(point);
        }
        glo::rot += 0.5;
        sf::Vertex closeLine[] = {glo::startCoords, glo::endCoords};
        closeLine[0].color = sf::Color(glo::colRandR, glo::colRandG, glo::colRandB);
        closeLine[1].color = sf::Color(glo::colRandR, glo::colRandG, glo::colRandB);
        window.draw(closeLine, 2, sf::Lines);
        window.draw(lines);
        // ---------- END ----------
        window.display();
    }
}

// ---------- VOIDS ----------
