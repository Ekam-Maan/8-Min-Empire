Things Left:
  Randomzing shuffle
  adding info for goods and actions

Structure Card:
  Will represent a single card
  Contains the following Info: title,good and action

Class Deck:
  will have a array of cards
  Constructor : number of players based on which the size of deck will be determined
  For more real life functionality, can shuffle the array

  The draw function will return the first card 
  will have a internal ptr to mark the top card

2 players (27 cards):
[
  'Ancient Phoenix',     'Ancient Sage',
  'Ancient Tree Spirit', 'Ancient Woods',
  'Cursed Banshee',      'Cursed Gargoyles',
  'Cursed King',         'Cursed Mausoleum',
  'Cursed Tower',        'Dire Dragon',
  'Dire Eye',            'Dire Giant',
  'Dire Goblin',         'Dire Ogre',
  'Forest Elf',          'Forest Gnome',
  'Forest Pixie',        'Forest Tree Town',
  'Graveyard',           'Lake',
  'Night Hydra',         'Night Village',
  'Night Wizard',        'Noble Hills',
  'Noble Knight',        'Noble Unicorn',
  'Stronghold'
]

3 players (32 cards):
[
  'Arcane Manticore',    'Arcane Sphinx',
  'Arcane Temple',       'Mountain Dwarf',
  'Mountain Treasury'
]

4 players (34 cards):
[
  'Castle',              'Castle 2'
]