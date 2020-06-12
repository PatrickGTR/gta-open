enum {
    E_TYPE_HAT,
    E_TYPE_GLASSES,
    E_TYPE_BANDANA,
    E_TYPE_HEADPHONES,
    E_TYPE_MASK,
    E_TYPE_BAG,
    E_TYPE_HELMET,
    E_TYPE_GUITAR
}

static enum E_MODEL {
    E_MODEL_TYPE,
    E_MODEL_ID,
    E_MODEL_NAME[MAX_ATTACHMENT_NAME],
    E_MODEL_PRICE,
    E_MODEL_BONEID
}

static const gModelInfo[][E_MODEL] =
{
    {E_TYPE_HAT, 18926, "Army Hat", 700, 2},
    {E_TYPE_HAT, 18927, "Azure Hat", 700, 2},
    {E_TYPE_HAT, 18928, "Funky Hat", 700, 2},
    {E_TYPE_HAT, 18929, "Dark Gray Hat", 700, 2},
    {E_TYPE_HAT, 18930, "Fire Hat", 700, 2},
    {E_TYPE_HAT, 18931, "Dark Blue Hat", 700, 2},
    {E_TYPE_HAT, 18932, "Orange Hat", 700, 2},
    {E_TYPE_HAT, 18933, "Light Gray Hat", 700, 2},
    {E_TYPE_HAT, 18934, "Pink Hat", 700, 2},
    {E_TYPE_HAT, 18935, "Yellow Hat", 700, 2},
    {E_TYPE_HAT, 18944, "Fire Hat Boater", 1000, 2},
    {E_TYPE_HAT, 18945, "Gray Hat Boater", 1000, 2},
    {E_TYPE_HAT, 18946, "Gray Hat Boater 2", 1000, 2},
    {E_TYPE_HAT, 18947, "Black Hat Bowler", 1000, 2},
    {E_TYPE_HAT, 18948, "Azure Hat Bowler", 1000, 2},
    {E_TYPE_HAT, 18949, "Green Hat Bowler", 1000, 2},
    {E_TYPE_HAT, 18950, "Red Hat Bowler", 1000, 2},
    {E_TYPE_HAT, 18951, "Light Green Hat Bowler", 1000, 2},
    {E_TYPE_HAT, 19488, "White Hat Bowler", 1000, 2},
    {E_TYPE_HAT, 18967, "Simple Black Hat", 500, 2},
    {E_TYPE_HAT, 18968, "Simple Gray Hat", 500, 2},
    {E_TYPE_HAT, 18969, "Simple Orange Hat", 500, 2},
    {E_TYPE_HAT, 18970, "Tiger Hat", 1000, 2},
    {E_TYPE_HAT, 18971, "Black & White Cool Hat", 1000, 2},
    {E_TYPE_HAT, 18972, "Black & Orange Cool Hat", 1000, 2},
    {E_TYPE_HAT, 18973, "Black & Green Cool Hat", 1000, 2},
    {E_TYPE_HAT, 19066, "Santa Hat", 3000, 2},
    {E_TYPE_HAT, 19067, "Red Hoody Hat", 500, 2},
    {E_TYPE_HAT, 19068, "Tiger Hoody Hat", 500, 2},
    {E_TYPE_HAT, 19069, "Black Hoody Hat", 500, 2},
    {E_TYPE_HAT, 19093, "White Dude Hat", 1300, 2},
    {E_TYPE_HAT, 19095, "Brown Cowboy Hat", 1300, 2},
    {E_TYPE_HAT, 19096, "Black Cowboy Hat", 1300, 2},
    {E_TYPE_HAT, 19097, "Black Cowboy Hat 2", 1300, 2},
    {E_TYPE_HAT, 19098, "Brown Cowboy Hat 2", 1300, 2},
    {E_TYPE_HAT, 19352, "Black Top Hat", 2000, 2},
    {E_TYPE_HAT, 19487, "White Top Hat", 2000, 2},
    {E_TYPE_HAT, 18964, "Black Skully Cap", 700, 2},
    {E_TYPE_HAT, 18965, "Brown Skully Cap", 700, 2},
    {E_TYPE_HAT, 18966, "Funky Skully Cap", 700, 2},
    {E_TYPE_HAT, 18921, "Blue Beret", 500, 2},
    {E_TYPE_HAT, 18922, "Red Beret", 500, 2},
    {E_TYPE_HAT, 18923, "Dark Blue Beret", 500, 2},
    {E_TYPE_HAT, 18924, "Army Beret", 500, 2},
    {E_TYPE_HAT, 18925, "Red Army Beret", 500, 2},
    {E_TYPE_HAT, 18939, "Dark Blue CapBack", 1000, 2},
    {E_TYPE_HAT, 18940, "Azure CapBack", 1000, 2},
    {E_TYPE_HAT, 18941, "Black CapBack", 1000, 2},
    {E_TYPE_HAT, 18942, "Gray CapBack", 1000, 2},
    {E_TYPE_HAT, 18943, "Green CapBack", 1000, 2},
    {E_TYPE_GLASSES, 19006, "Red Glasses", 1000, 2},
    {E_TYPE_GLASSES, 19007, "Green Glasses", 1000, 2},
    {E_TYPE_GLASSES, 19008, "Yellow Glasses", 1000, 2},
    {E_TYPE_GLASSES, 19009, "Azure Glasses", 1000, 2},
    {E_TYPE_GLASSES, 19010, "Pink Glasses", 1000, 2},
    {E_TYPE_GLASSES, 19011, "Funky Glasses", 1000, 2},
    {E_TYPE_GLASSES, 19012, "Gray Glasses", 1000, 2},
    {E_TYPE_GLASSES, 19013, "Funky Glasses 2", 1000, 2},
    {E_TYPE_GLASSES, 19014, "Black & White Glasses", 1000, 2},
    {E_TYPE_GLASSES, 19015, "White Glasses", 1000, 2},
    {E_TYPE_GLASSES, 19016, "X-Ray Glasses", 3000, 2},
    {E_TYPE_GLASSES, 19017, "Yellow Glasses", 1000, 2},
    {E_TYPE_GLASSES, 19018, "Orange Glasses", 1000, 2},
    {E_TYPE_GLASSES, 19019, "Red Glasses", 1000, 2},
    {E_TYPE_GLASSES, 19020, "Blue Glasses", 1000, 2},
    {E_TYPE_GLASSES, 19021, "Green Glasses", 1000, 2},
    {E_TYPE_GLASSES, 19022, "Black Glasses", 1000, 2},
    {E_TYPE_GLASSES, 19023, "Azure Glasses", 1000, 2},
    {E_TYPE_GLASSES, 19024, "Blue Glasses", 1000, 2},
    {E_TYPE_GLASSES, 19025, "Pink Glasses", 1000, 2},
    {E_TYPE_GLASSES, 19026, "Red Glasses", 1000, 2},
    {E_TYPE_GLASSES, 19027, "Orange Glasses", 1000, 2},
    {E_TYPE_GLASSES, 19028, "Yellow Glasses", 1000, 2},
    {E_TYPE_GLASSES, 19029, "Yellow Glasses", 1000, 2},
    {E_TYPE_GLASSES, 19030, "Pink Nerd Glasses", 1500, 2},
    {E_TYPE_GLASSES, 19031, "Green Nerd Glasses", 1500, 2},
    {E_TYPE_GLASSES, 19032, "Red Nerd Glasses", 1500, 2},
    {E_TYPE_GLASSES, 19033, "Black Nerd Glasses", 1500, 2},
    {E_TYPE_GLASSES, 19034, "Black & White Nerd Glasses", 1500, 2},
    {E_TYPE_GLASSES, 19035, "Ocean Nerd Glasses", 1500, 2},
    {E_TYPE_BANDANA, 18891, "Purple Bandana", 1200, 2},
    {E_TYPE_BANDANA, 18892, "Red Bandana", 1200, 2},
    {E_TYPE_BANDANA, 18893, "Red&White Bandana", 1200, 2},
    {E_TYPE_BANDANA, 18894, "Orange Bandana", 1200, 2},
    {E_TYPE_BANDANA, 18895, "Skull Bandana", 1200, 2},
    {E_TYPE_BANDANA, 18896, "Black Bandana", 1200, 2},
    {E_TYPE_BANDANA, 18897, "Blue Bandana", 1200, 2},
    {E_TYPE_BANDANA, 18898, "Green Bandana", 1200, 2},
    {E_TYPE_BANDANA, 18899, "Pink Bandana", 1200, 2},
    {E_TYPE_BANDANA, 18900, "Funky Bandana", 1200, 2},
    {E_TYPE_BANDANA, 18901, "Tiger Bandana", 1200, 2},
    {E_TYPE_BANDANA, 18902, "Yellow Bandana", 1200, 2},
    {E_TYPE_BANDANA, 18903, "Azure Bandana", 1200, 2},
    {E_TYPE_BANDANA, 18904, "Dark Blue Bandana", 1200, 2},
    {E_TYPE_BANDANA, 18905, "Olive Bandana", 1200, 2},
    {E_TYPE_BANDANA, 18906, "Orange&Yellow Bandana", 800, 2},
    {E_TYPE_BANDANA, 18907, "Funky Bandana 2", 800, 2},
    {E_TYPE_BANDANA, 18907, "Blue Bandana 2", 800, 2},
    {E_TYPE_BANDANA, 18907, "Azure Bandana 2", 800, 2},
    {E_TYPE_BANDANA, 18907, "Fire Bandana", 800, 2},
    {E_TYPE_HEADPHONES, 18911, "Skull Bandana Mask", 1200, 18},
    {E_TYPE_HEADPHONES, 18912, "Black Bandana Mask", 1200, 18},
    {E_TYPE_HEADPHONES, 18913, "Green Bandana Mask", 1200, 18},
    {E_TYPE_HEADPHONES, 18914, "Army Bandana Mask", 1200, 18},
    {E_TYPE_HEADPHONES, 18915, "Funky Bandana Mask", 1200, 18},
    {E_TYPE_HEADPHONES, 18916, "Light Bandana Mask", 1200, 18},
    {E_TYPE_HEADPHONES, 18917, "Dark Blue Bandana Mask", 1200, 18},
    {E_TYPE_HEADPHONES, 18918, "Gray Bandana Mask", 1200, 18},
    {E_TYPE_HEADPHONES, 18919, "White Bandana Mask", 1200, 18},
    {E_TYPE_HEADPHONES, 18920, "Colorful Bandana Mask", 1200, 18},
    {E_TYPE_HEADPHONES, 19421, "White Headphones", 2000, 2},
    {E_TYPE_HEADPHONES, 19422, "Black Headphones", 2000, 2},
    {E_TYPE_HEADPHONES, 19423, "Gray Headphones", 2000, 2},
    {E_TYPE_HEADPHONES, 19424, "Blue Headphones", 2000, 2},
    {E_TYPE_MASK, 19036, "White Hockey Mask", 1200, 2},
    {E_TYPE_MASK, 19037, "Red Hockey Mask", 1200, 2},
    {E_TYPE_MASK, 19038, "Green Hockey Mask", 1200, 2},
    {E_TYPE_MASK, 19472, "Gas Mask", 2000, 2},
    {E_TYPE_BAG, 2919, "Sports Bag", 1500, 5},
    {E_TYPE_BAG, 3026, "Jansport Backpack", 1500, 1},
    {E_TYPE_HELMET, 18645, "Red & White Motorcycle Helmet", 4000, 2},
    {E_TYPE_HELMET, 18976, "Blue Motorcycle Helmet", 4000, 2},
    {E_TYPE_HELMET, 18977, "Red Motorcycle Helmet", 4000, 2},
    {E_TYPE_HELMET, 18978, "White Motorcycle Helmet", 4000, 2},
    {E_TYPE_HELMET, 18979, "Purple Motorcycle Helmet", 4000, 2},
    {E_TYPE_GUITAR, 19317, "Bass Guitar", 14000 ,1},
    {E_TYPE_GUITAR, 19318, "Flying Guitar", 15000, 1},
    {E_TYPE_GUITAR, 19319, "Warlock Guitar", 16000, 1}
};

stock Attachment_GetType(index) {
    if(NOT_IN_RANGE(index, 0, Attachment_GetTotalModels())) {
        return -1;
    }
    return gModelInfo[index][E_MODEL_TYPE];
}

// returns the model id of the model by given index.
stock Attachment_GetModelID(index) {
    if(NOT_IN_RANGE(index, 0, Attachment_GetTotalModels())) {
        return -1;
    }
    return gModelInfo[index][E_MODEL_ID];
}

// returns the bone id of the model by given index.
stock Attachment_GetModelBoneID(index) {
    if(NOT_IN_RANGE(index, 0, Attachment_GetTotalModels())) {
        return -1;
    }
    return gModelInfo[index][E_MODEL_BONEID];
}

// returns the price of the model by given index.
stock Attachment_GetModelPrice(index) {
    if(NOT_IN_RANGE(index, 0, Attachment_GetTotalModels())) {
        return -1;
    }
    return gModelInfo[index][E_MODEL_PRICE];
}

// returns the value of the array.
stock Attachment_GetTotalModels() {
    return sizeof(gModelInfo);
}

// returns the name of the attachment base on given index.
stock Attachment_GetModelName(modelid, name[], len = sizeof(name)) {
    for(new i = 0; i < sizeof(gModelInfo); i++) {
        if (modelid == gModelInfo[i][E_MODEL_ID]) {
            strcpy(name, gModelInfo[i][E_MODEL_NAME], len);
			break;
        }
    }
    return 1;
}