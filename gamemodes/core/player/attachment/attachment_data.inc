enum E_MODEL {
    E_MODEL_ID,
    E_MODEL_NAME[MAX_ATTACHMENT_NAME],
    E_MODEL_PRICE,
    E_MODEL_BONEID
}

static const gModelInfo[][E_MODEL] = 
{
    {18926, "Army Hat", 700, 2},
    {18927, "Azure Hat", 700, 2},
    {18928, "Funky Hat", 700, 2},
    {18929, "Dark Gray Hat", 700, 2},
    {18930, "Fire Hat", 700, 2},
    {18931, "Dark Blue Hat", 700, 2},
    {18932, "Orange Hat", 700, 2},
    {18933, "Light Gray Hat", 700, 2},
    {18934, "Pink Hat", 700, 2},
    {18935, "Yellow Hat", 700, 2},
    {18944, "Fire Hat Boater", 1000, 2},
    {18945, "Gray Hat Boater", 1000, 2},
    {18946, "Gray Hat Boater 2", 1000, 2},
    {18947, "Black Hat Bowler", 1000, 2},
    {18948, "Azure Hat Bowler", 1000, 2},
    {18949, "Green Hat Bowler", 1000, 2},
    {18950, "Red Hat Bowler", 1000, 2},
    {18951, "Light Green Hat Bowler", 1000, 2},
    {19488, "White Hat Bowler", 1000, 2},
    {18967, "Simple Black Hat", 500, 2},
    {18968, "Simple Gray Hat", 500, 2},
    {18969, "Simple Orange Hat", 500, 2},
    {18970, "Tiger Hat", 1000, 2},
    {18971, "Black & White Cool Hat", 1000, 2},
    {18972, "Black & Orange Cool Hat", 1000, 2},
    {18973, "Black & Green Cool Hat", 1000, 2},
    {19066, "Santa Hat", 3000, 2},
    {19067, "Red Hoody Hat", 500, 2},
    {19068, "Tiger Hoody Hat", 500, 2},
    {19069, "Black Hoody Hat", 500, 2},
    {19093, "White Dude Hat", 1300, 2},
    {19095, "Brown Cowboy Hat", 1300, 2},
    {19096, "Black Cowboy Hat", 1300, 2},
    {19097, "Black Cowboy Hat 2", 1300, 2},
    {19098, "Brown Cowboy Hat 2", 1300, 2},
    {19352, "Black Top Hat", 2000, 2},
    {19487, "White Top Hat", 2000, 2},
    {18964, "Black Skully Cap", 700, 2},
    {18965, "Brown Skully Cap", 700, 2},
    {18966, "Funky Skully Cap", 700, 2},
    {18921, "Blue Beret", 500, 2},
    {18922, "Red Beret", 500, 2},
    {18923, "Dark Blue Beret", 500, 2},
    {18924, "Army Beret", 500, 2},
    {18925, "Red Army Beret", 500, 2},
    {18939, "Dark Blue CapBack", 1000, 2},
    {18940, "Azure CapBack", 1000, 2},
    {18941, "Black CapBack", 1000, 2},
    {18942, "Gray CapBack", 1000, 2},
    {18943, "Green CapBack", 1000, 2},
    {19006, "Red Glasses", 1000, 2},
    {19007, "Green Glasses", 1000, 2},
    {19008, "Yellow Glasses", 1000, 2},
    {19009, "Azure Glasses", 1000, 2},
    {19010, "Pink Glasses", 1000, 2},
    {19011, "Funky Glasses", 1000, 2},
    {19012, "Gray Glasses", 1000, 2},
    {19013, "Funky Glasses 2", 1000, 2},
    {19014, "Black & White Glasses", 1000, 2},
    {19015, "White Glasses", 1000, 2},
    {19016, "X-Ray Glasses", 3000, 2},
    {19017, "Covered Yellow Glasses", 1000, 2},
    {19018, "Covered Orange Glasses", 1000, 2},
    {19019, "Covered Red Glasses", 1000, 2},
    {19020, "Covered Blue Glasses", 1000, 2},
    {19021, "Covered Green Glasses", 1000, 2},
    {19022, "Cool Black Glasses", 1000, 2},
    {19023, "Cool Azure Glasses", 1000, 2},
    {19024, "Cool Blue Glasses", 1000, 2},
    {19025, "Cool Pink Glasses", 1000, 2},
    {19026, "Cool Red Glasses", 1000, 2},
    {19027, "Cool Orange Glasses", 1000, 2},
    {19028, "Cool Yellow Glasses", 1000, 2},
    {19029, "Cool Yellow Glasses", 1000, 2},
    {19030, "Pink Nerd Glasses", 1500, 2},
    {19031, "Green Nerd Glasses", 1500, 2},
    {19032, "Red Nerd Glasses", 1500, 2},
    {19033, "Black Nerd Glasses", 1500, 2},
    {19034, "Black & White Nerd Glasses", 1500, 2},
    {19035, "Ocean Nerd Glasses", 1500, 2},
    {18891, "Purple Bandana", 1200, 2},
    {18892, "Red Bandana", 1200, 2},
    {18893, "Red&White Bandana", 1200, 2},
    {18894, "Orange Bandana", 1200, 2},
    {18895, "Skull Bandana", 1200, 2},
    {18896, "Black Bandana", 1200, 2},
    {18897, "Blue Bandana", 1200, 2},
    {18898, "Green Bandana", 1200, 2},
    {18899, "Pink Bandana", 1200, 2},
    {18900, "Funky Bandana", 1200, 2},
    {18901, "Tiger Bandana", 1200, 2},
    {18902, "Yellow Bandana", 1200, 2},
    {18903, "Azure Bandana", 1200, 2},
    {18904, "Dark Blue Bandana", 1200, 2},
    {18905, "Olive Bandana", 1200, 2},
    {18906, "Orange&Yellow Bandana", 800, 2},
    {18907, "Funky Bandana 2", 800, 2},
    {18907, "Blue Bandana 2", 800, 2},
    {18907, "Azure Bandana 2", 800, 2},
    {18907, "Fire Bandana", 800, 2},
    {18911, "Skull Bandana Mask", 1200, 18},
    {18912, "Black Bandana Mask", 1200, 18},
    {18913, "Green Bandana Mask", 1200, 18},
    {18914, "Army Bandana Mask", 1200, 18},
    {18915, "Funky Bandana Mask", 1200, 18},
    {18916, "Light Bandana Mask", 1200, 18},
    {18917, "Dark Blue Bandana Mask", 1200, 18},
    {18918, "Gray Bandana Mask", 1200, 18},
    {18919, "White Bandana Mask", 1200, 18},
    {18920, "Colorful Bandana Mask", 1200, 18},
    {19421, "White Headphones", 2000, 2},
    {19422, "Black Headphones", 2000, 2},
    {19423, "Gray Headphones", 2000, 2},
    {19424, "Blue Headphones", 2000, 2},
    {19036, "White Hockey Mask", 1200, 2},
    {19037, "Red Hockey Mask", 1200, 2},
    {19038, "Green Hockey Mask", 1200, 2},
    {19472, "Gas Mask", 2000, 2},
    {2919, "Sports Bag", 1500, 5},
    {3026, "Jansport Backpack", 1500, 1},
    {18645, "Red & White Motorcycle Helmet", 4000, 2},
    {18976, "Blue Motorcycle Helmet", 4000, 2},
    {18977, "Red Motorcycle Helmet", 4000, 2},
    {18978, "White Motorcycle Helmet", 4000, 2},
    {18979, "Purple Motorcycle Helmet", 4000, 2},
    {19317, "Bass Guitar", 14000 ,1},
    {19318, "Flying Guitar", 15000, 1},
    {19319, "Warlock Guitar", 16000, 1}
};

// returns the model id of the model by given index.
stock Attachment_GetModelID(index) {
    if(index > sizeof(gModelInfo)) {
        return -1;
    }
    return gModelInfo[index][E_MODEL_ID];
}

// returns the bone id of the model by given index.
stock Attachment_GetModelBoneID(index) {
    if(index > sizeof(gModelInfo)) {
        return -1;
    }
    return gModelInfo[index][E_MODEL_BONEID];
}

// returns the price of the model by given index.
stock Attachment_GetModelPrice(index) {
    if(index > sizeof(gModelInfo)) {
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