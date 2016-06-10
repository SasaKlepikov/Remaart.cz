<?php

/**
 * @file
 *  Migrations for commerce_kickstart_lite_product.
 */
class CommerceKickstartProduct extends CommerceKickstartMigration {

  public function __construct() {
    parent::__construct();
    $this->description = t('Import products.');

    // Create a map object for tracking the relationships between source rows
    $this->map = new MigrateSQLMap($this->machineName, array(
      'sku' => array(
        'type' => 'varchar',
        'length' => 32,
        'not null' => TRUE,
      ),
        ), MigrateDestinationEntityAPI::getKeySchema('commerce_product', 'product')
    );

    // Create a MigrateSource object.
    $this->source = new MigrateSourceCSV(drupal_get_path('module', 'commerce_kickstart_lite_product') . '/import/products.csv', $this->csvcolumns(), array('header_rows' => 1), $this->fields());

    $this->destination = new MigrateDestinationEntityAPI('commerce_product', 'product');

    $this->addFieldMapping('title', 'title');
    $this->addFieldMapping('sku', 'sku');
    $this->addFieldMapping('commerce_price', 'price');
    $this->addFieldMapping('commerce_price:currency_code', NULL)
          ->defaultValue('CZK');
    $this->addFieldMapping('commerce_price:tax_rate', 'price_tax')
          ->defaultValue('dph_21');

    // Images
    $this->addFieldMapping('field_images', 'product_images');
    $this->addFieldMapping('field_images:file_replace')
        ->defaultValue(FILE_EXISTS_REPLACE);
    $this->addFieldMapping('field_images:source_dir')
        ->defaultValue(drupal_get_path('module', 'commerce_kickstart_lite_product') . '/import/images');

    $this->addFieldMapping('uid', 'uid');
    $this->addFieldMapping('language', 'language');
  }

  function csvcolumns() {
    $columns[0] = array('title', 'Title');
    $columns[1] = array('sku', 'SKU');
    $columns[2] = array('price', 'Price');
    $columns[3] = array('images', 'Images');
    $columns[4] = array('category', 'Category');
    return $columns;
  }

  function fields() {
    return array(
      'product_images' => 'An array of images, populated during prepareRow().',
    );
  }

  function prepareRow($row) {
    $row->product_images = explode(', ', $row->images);
    $row->uid = 1;
    $row->language = LANGUAGE_NONE;
  }

}

class CommerceKickstartNode extends CommerceKickstartMigration {

  public function __construct() {
    parent::__construct();
    $this->description = t('Import product nodes.');

    $this->dependencies = array(
      'CommerceKickstartProduct',
    );

    // Create a map object for tracking the relationships between source rows
    $this->map = new MigrateSQLMap($this->machineName, array(
      'title' => array(
        'type' => 'varchar',
        'length' => 255,
        'not null' => TRUE,
      ),
        ), MigrateDestinationNode::getKeySchema()
    );

    // Create a MigrateSource object.
    $this->source = new MigrateSourceCSV(drupal_get_path('module', 'commerce_kickstart_lite_product') . '/import/nodes.csv', $this->csvcolumns(), array('header_rows' => 1));

    $this->destination = new MigrateDestinationNode('product_display');

    $this->addFieldMapping('uid', 'uid')->defaultValue(1);

    $this->addFieldMapping('title', 'title');
    $this->addFieldMapping('body', 'description');
    $this->addFieldMapping('body:summary', 'excerpt');
    $this->addFieldMapping('field_product_category', 'category');
    $this->addFieldMapping('field_product_category:create_term')
        ->defaultValue(TRUE);
    $this->addFieldMapping('field_product', 'skus');
  }

  public function prepareRow($row) {
    $products = array();
    foreach (explode(', ', $row->sku) as $sku) {
      $product = commerce_product_load_by_sku($sku);
      $products[] = $product->product_id;
    }
    $row->skus = $products;
  }

  function csvcolumns() {
    $columns[0] = array('title', 'Title');
    $columns[1] = array('description', 'Description');
    $columns[2] = array('category', 'Category');
    $columns[3] = array('sku', 'SKU');
    return $columns;
  }

}

class CommerceKickstartObrazyVarianty extends CommerceKickstartMigration {

  public function __construct() {
    parent::__construct();
    $this->description = t('Import variant obrazů.');

    // Create a map object for tracking the relationships between source rows
    $this->map = new MigrateSQLMap($this->machineName, array(
      'sku' => array(
        'type' => 'varchar',
        'length' => 32,
        'not null' => TRUE,
      ),
        ), MigrateDestinationEntityAPI::getKeySchema('commerce_product', 'obraz')
    );

    // Create a MigrateSource object.
    $this->source = new MigrateSourceCSV(drupal_get_path('module', 'commerce_kickstart_lite_product') . '/import/obrazy-varianty.csv', $this->csvcolumns(), array('header_rows' => 1), $this->fields());

    $this->destination = new MigrateDestinationEntityAPI('commerce_product', 'obraz');
    
    $this->addFieldMapping('uid', 'uid')->defaultValue(1);
    $this->addFieldMapping('language', 'language')->defaultValue('cs');
    $this->addFieldMapping('title', 'title');
    $this->addFieldMapping('sku', 'sku');
    $this->addFieldMapping('commerce_price', 'price');
    $this->addFieldMapping('commerce_price:currency_code', NULL)
          ->defaultValue('CZK');
    $this->addFieldMapping('commerce_price:tax_rate', 'price_tax')
          ->defaultValue('dph_21');
    $this->addFieldMapping('field_images', 'product_images');
    $this->addFieldMapping('field_images:file_replace')
        ->defaultValue(FILE_EXISTS_REPLACE);
    $this->addFieldMapping('field_images:source_dir')
        ->defaultValue(drupal_get_path('module', 'commerce_kickstart_lite_product') . '/import/images');
    $this->addFieldMapping('field_typ_obrazu', 'typ_obrazu');
    $this->addFieldMapping('field_bezna_cena', 'bezna_cena');
    $this->addFieldMapping('field_doba_dodani', 'doba_dodani');
    $this->addFieldMapping('field_rozmery_obrazu', 'rozmery_obrazu');
    $this->addFieldMapping('field_rozmery_obrazu:create_term')
        ->defaultValue(TRUE);
    $this->addFieldMapping('field_umisteni_hodin', 'umisteni');
    $this->addFieldMapping('field_description', 'popis');
    $this->addFieldMapping('field_description:summary', 'excerpt');
    $this->addFieldMapping('field_tagy', 'tagy');
    $this->addFieldMapping('field_tagy:create_term')
        ->defaultValue(TRUE);
    $this->addFieldMapping('field_rozmery_dilu_obrazu', 'dily');
    $this->addFieldMapping('field_rozmery_dilu_obrazu:create_term')
        ->defaultValue(TRUE);
    $this->addFieldMapping('field_s_hodinami', 'hodiny');
  }

  function csvcolumns() {
    $columns[0] = array('title', 'Title');
    $columns[1] = array('sku', 'SKU');
    $columns[2] = array('price', 'Price');
    $columns[3] = array('images', 'Images');
    $columns[4] = array('typ_obrazu', 'Typ obrazu');
    $columns[5] = array('bezna_cena', 'Standardni cena');
    $columns[6] = array('doba_dodani', 'Doba dodani');
    $columns[7] = array('rozmery_obrazu', 'Rozmery obrazu');
    $columns[8] = array('umisteni', 'Umisteni');
    $columns[9] = array('popis', 'Description');
    $columns[10] = array('tags', 'Tagy');
    $columns[11] = array('dily', 'Rozmery dilu');
    $columns[12] = array('hodiny', 'Hodiny');
    return $columns;
  }

  function fields() {
    return array(
      'product_images' => 'An array of images, populated during prepareRow().',
    );
  }

  function prepareRow($row) {
    $row->product_images = explode(', ', $row->images);
    $row->tagy = explode(', ', $row->tags);
  }

}

class CommerceKickstartObrazyNodes extends CommerceKickstartMigration {

  public function __construct() {
    parent::__construct();
    $this->description = t('Import stránek (nodes) s obrazy.');

    // Create a map object for tracking the relationships between source rows
    $this->map = new MigrateSQLMap($this->machineName, array(
      'node_id' => array(
        'type' => 'varchar',
        'length' => 255,
        'not null' => TRUE,
      ),
        ), MigrateDestinationNode::getKeySchema()
    );

    // Create a MigrateSource object.
    $this->source = new MigrateSourceCSV(drupal_get_path('module', 'commerce_kickstart_lite_product') . '/import/obrazy-nodes.csv', $this->csvcolumns(), array('header_rows' => 1));

    $this->destination = new MigrateDestinationNode('obraz');

    $this->addFieldMapping('uid', 'uid')->defaultValue(1);

    $this->addFieldMapping('title', 'title');
    $this->addFieldMapping('field_product_category', 'category');
    $this->addFieldMapping('field_product', 'skus');
    $this->addFieldMapping('language', 'language')->defaultValue('cs');
    $this->addFieldMapping('node_id', 'node_id');
  }

  public function prepareRow($row) {
    $products = array();
    foreach (explode(', ', $row->sku) as $sku) {
      $product = commerce_product_load_by_sku($sku);
      $products[] = $product->product_id;
    }
    $row->skus = $products;
  }

  function csvcolumns() {
    $columns[0] = array('node_id', 'NodeID');
    $columns[1] = array('title', 'Title');
    $columns[2] = array('category', 'Category');
    $columns[3] = array('sku', 'SKU');
    return $columns;
  }

}

class CommerceKickstartFototapetyVarianty extends CommerceKickstartMigration {

  public function __construct() {
    parent::__construct();
    $this->description = t('Import variant fototapet.');

    // Create a map object for tracking the relationships between source rows
    $this->map = new MigrateSQLMap($this->machineName, array(
      'sku' => array(
        'type' => 'varchar',
        'length' => 32,
        'not null' => TRUE,
      ),
        ), MigrateDestinationEntityAPI::getKeySchema('commerce_product', 'fototapety')
    );

    // Create a MigrateSource object.
    $this->source = new MigrateSourceCSV(drupal_get_path('module', 'commerce_kickstart_lite_product') . '/import/fototapety-varianty.csv', $this->csvcolumns(), array('header_rows' => 1), $this->fields());

    $this->destination = new MigrateDestinationEntityAPI('commerce_product', 'fototapety');
    
    $this->addFieldMapping('uid', 'uid')->defaultValue(1);
    $this->addFieldMapping('language', 'language')->defaultValue('cs');
    $this->addFieldMapping('title', 'title');
    $this->addFieldMapping('sku', 'sku');
    $this->addFieldMapping('commerce_price', 'price');
    $this->addFieldMapping('commerce_price:currency_code', NULL)
          ->defaultValue('CZK');
    $this->addFieldMapping('commerce_price:tax_rate', 'price_tax')
          ->defaultValue('dph_21');
    $this->addFieldMapping('field_images', 'product_images');
    $this->addFieldMapping('field_images:file_replace')
        ->defaultValue(FILE_EXISTS_REPLACE);
    /*$this->addFieldMapping('field_images:source_dir')
        ->defaultValue(drupal_get_path('module', 'commerce_kickstart_lite_product') . '/import/images');*/
    $this->addFieldMapping('field_description', 'popis');
    $this->addFieldMapping('field_description:summary', 'excerpt');
  }

  function csvcolumns() {
    $columns[0] = array('title', 'PRODUCTNAME');
    $columns[1] = array('popis', 'DESCRIPTION');
    $columns[2] = array('images', 'IMGURL');
    $columns[3] = array('price', 'PRICE');
    $columns[4] = array('sku', 'CODE');
    return $columns;
  }

  function fields() {
    return array(
      'product_images' => 'An array of images, populated during prepareRow().',
    );
  }

  function prepareRow($row) {
    $row->product_images = explode(', ', $row->images);
  }
}

class CommerceKickstartFototapetyNodes extends CommerceKickstartMigration {

  public function __construct() {
    parent::__construct();
    $this->description = t('Import stránek (nodes) s fototapetami.');

    // Create a map object for tracking the relationships between source rows
    $this->map = new MigrateSQLMap($this->machineName, array(
      'node_id' => array(
        'type' => 'varchar',
        'length' => 255,
        'not null' => TRUE,
      ),
        ), MigrateDestinationNode::getKeySchema()
    );

    // Create a MigrateSource object.
    $this->source = new MigrateSourceCSV(drupal_get_path('module', 'commerce_kickstart_lite_product') . '/import/fototapety-nodes.csv', $this->csvcolumns(), array('header_rows' => 1));

    $this->destination = new MigrateDestinationNode('fototapety');

    $this->addFieldMapping('uid', 'uid')->defaultValue(1);

    $this->addFieldMapping('title', 'title');
    $this->addFieldMapping('field_product_category', 'category')->defaultValue('Fototapety');
    $this->addFieldMapping('field_product', 'skus');
    $this->addFieldMapping('language', 'language')->defaultValue('cs');
    $this->addFieldMapping('node_id', 'node_id');
  }

  public function prepareRow($row) {
    $products = array();
    foreach (explode(', ', $row->sku) as $sku) {
      $product = commerce_product_load_by_sku($sku);
      $products[] = $product->product_id;
    }
    $row->skus = $products;
  }

  function csvcolumns() {
    $columns[0] = array('node_id', 'NodeID');
    $columns[1] = array('title', 'Title');
    $columns[2] = array('sku', 'SKU');
    return $columns;
  }

}

class CommerceKickstartNabytekDoplnkyVarianty extends CommerceKickstartMigration {

  public function __construct() {
    parent::__construct();
    $this->description = t('Import variant Nabytku a Doplňků.');

    // Create a map object for tracking the relationships between source rows
    $this->map = new MigrateSQLMap($this->machineName, array(
      'sku' => array(
        'type' => 'varchar',
        'length' => 32,
        'not null' => TRUE,
      ),
        ), MigrateDestinationEntityAPI::getKeySchema('commerce_product', 'nabytek')
    );

    // Create a MigrateSource object.
    $this->source = new MigrateSourceCSV(drupal_get_path('module', 'commerce_kickstart_lite_product') . '/import/nabytekdoplnky-varianty.csv', $this->csvcolumns(), array('header_rows' => 1), $this->fields());

    $this->destination = new MigrateDestinationEntityAPI('commerce_product', 'nabytek');
    
    $this->addFieldMapping('uid', 'uid')->defaultValue(1);
    $this->addFieldMapping('language', 'language')->defaultValue('cs');
    $this->addFieldMapping('title', 'title');
    $this->addFieldMapping('sku', 'sku');
    $this->addFieldMapping('commerce_price', 'price');
    $this->addFieldMapping('commerce_price:currency_code', NULL)
          ->defaultValue('CZK');
    $this->addFieldMapping('commerce_price:tax_rate', 'price_tax')
          ->defaultValue('dph_21');
    $this->addFieldMapping('field_images', 'product_images');
    $this->addFieldMapping('field_images:file_replace')
        ->defaultValue(FILE_EXISTS_REPLACE);
    $this->addFieldMapping('field_images:source_dir')
        ->defaultValue(drupal_get_path('module', 'commerce_kickstart_lite_product') . '/import/images');
    $this->addFieldMapping('field_description', 'popis');
    $this->addFieldMapping('field_description:summary', 'excerpt');
    $this->addFieldMapping('field_sleva', 'sleva');
    $this->addFieldMapping('field_sleva:create_term')
        ->defaultValue(TRUE);
    $this->addFieldMapping('field_kategorie_nabytku', 'kategorie');
    $this->addFieldMapping('field_kategorie_nabytku:create_term')
        ->defaultValue(TRUE);
    $this->addFieldMapping('field_parametry', 'parametry');
    $this->addFieldMapping('field_parametry:summary', 'excerpt');
    $this->addFieldMapping('field_doporucujeme', 'doporucujeme');
    $this->addFieldMapping('field_tip_na_darek', 'darek');
    $this->addFieldMapping('field_material', 'material');
    $this->addFieldMapping('field_material:create_term')
        ->defaultValue(TRUE);
    $this->addFieldMapping('field_doba_dodani', 'dostupnost');
    $this->addFieldMapping('field_dodavatel', 'dodavatel');
    $this->addFieldMapping('field_dodavatel:create_term')
        ->defaultValue(TRUE);
    $this->addFieldMapping('field_bezna_cena', 'standard_price');
    $this->addFieldMapping('field_rozmery', 'rozmery');
    $this->addFieldMapping('field_rozmery:create_term')
        ->defaultValue(TRUE);
    $this->addFieldMapping('field_barvy', 'colors');
    $this->addFieldMapping('field_barvy:create_term')
        ->defaultValue(TRUE);
  }

  function csvcolumns() {
    $columns[0] = array('title', 'PRODUCTNAME');
    $columns[1] = array('popis', 'DESCRIPTION');
    $columns[2] = array('images', 'IMGURL');
    $columns[3] = array('price', 'PRICE');
    $columns[4] = array('sku', 'CODE');
    $columns[5] = array('sleva', 'SLEVA');
    $columns[6] = array('kategorie', 'KATEGORIE');
    $columns[7] = array('parametry', 'PARAMETRY');
    $columns[8] = array('akce', 'AKCE');
    $columns[9] = array('doporucujeme', 'DOPORUCUJEME');
    $columns[10] = array('darek', 'DAREK');
    $columns[11] = array('material', 'MATERIAL');
    $columns[12] = array('dostupnost', 'DOSTUPNOST');
    $columns[13] = array('standard_price', 'STANDARD_PRICE');
    $columns[14] = array('rozmery', 'ROZMERY');
    $columns[15] = array('barvy', 'BARVY');
    return $columns;
  }

  function fields() {
    return array(
      'product_images' => 'An array of images, populated during prepareRow().',
    );
  }

  function prepareRow($row) {
    $row->product_images = explode(', ', $row->images);
    $row->colors = explode(', ', $row->barvy);
  }
}

class CommerceKickstartNabytekDoplnkyNodes extends CommerceKickstartMigration {

  public function __construct() {
    parent::__construct();
    $this->description = t('Import stránek (nodes) s fototapetami.');

    // Create a map object for tracking the relationships between source rows
    $this->map = new MigrateSQLMap($this->machineName, array(
      'node_id' => array(
        'type' => 'varchar',
        'length' => 255,
        'not null' => TRUE,
      ),
        ), MigrateDestinationNode::getKeySchema()
    );

    // Create a MigrateSource object.
    $this->source = new MigrateSourceCSV(drupal_get_path('module', 'commerce_kickstart_lite_product') . '/import/nabytekdoplnky-nodes.csv', $this->csvcolumns(), array('header_rows' => 1));

    $this->destination = new MigrateDestinationNode('nabytek');

    $this->addFieldMapping('uid', 'uid')->defaultValue(1);

    $this->addFieldMapping('title', 'title');
    $this->addFieldMapping('field_product_category', 'category')->defaultValue('Nábytek & doplňky');
    $this->addFieldMapping('field_product', 'skus');
    $this->addFieldMapping('language', 'language')->defaultValue('cs');
    $this->addFieldMapping('node_id', 'node_id');
  }

  public function prepareRow($row) {
    $products = array();
    foreach (explode(', ', $row->sku) as $sku) {
      $product = commerce_product_load_by_sku($sku);
      $products[] = $product->product_id;
    }
    $row->skus = $products;
  }

  function csvcolumns() {
    $columns[0] = array('node_id', 'ID');
    $columns[1] = array('title', 'PRODUCTNAME');
    $columns[2] = array('sku', 'CODE');
    return $columns;
  }

}