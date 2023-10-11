# SpriteBatch

Simple spritebatch library for SFML written in C++.

### Install

Download the latest version and link statically the .lib file and include the .h file in your code

    ...
    #include <SpriteBatch.h>
    ...

### Usage

First construct the spritebatch class and initialize it with a reference to an existing texture, for now only one.

    ...
    sf::Texture t;
    t.loadFromFile("....");
    
    sfex::SpriteBatch batch;
    batch.Init(t);
    ...
Then every cycle of your application use the Begin function to resize the vertexarray in the batch.

    //Update all the entities
    ...
    batch.Begin(entities.size());
    ...
    
Now submit every sprite in the batch 
**IMPORTANT: entities must inherit from the sf::Sprite class**
In fact the Submit function take a const reference of a sf::Sprite

    ...
    for (const auto& entity : entities)
    {
        batch.Submit(entity);
    }
    ...
    
Finally draw the batch 

    ...
    win.draw(batch);
    ...
    
Anyways you can find an example in the *Testing* directory