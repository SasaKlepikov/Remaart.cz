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
    $this->map = new MigrateSQLMap($this->machineName,
      array(
        'sku' => array(
          'type' => 'varchar',
          'length' => 32,
          'not null' => TRUE,
        ),
      ),
      MigrateDestinationEntityAPI::getKeySchema('commerce_product', 'product')
    );

    // Create a MigrateSource object.
    $this->source = new MigrateSourceCSV(drupal_get_path('module', 'commerce_kickstart_lite_product') . '/import/products.csv', $this->csvcolumns(), array('header_rows' => 1), $this->fields());

    $this->destination = new MigrateDestinationEntityAPI('commerce_product', 'product');

    $this->addFieldMapping('title', 'title');
    $this->addFieldMapping('sku', 'sku');
    $this->addFieldMapping('commerce_price', 'price');

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
    $this->map = new MigrateSQLMap($this->machineName,
      array(
        'title' => array(
          'type' => 'varchar',
          'length' => 255,
          'not null' => TRUE,
        ),
      ),
      MigrateDestinationNode::getKeySchema()
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
    $this->map = new MigrateSQLMap($this->machineName,
      array(
        'sku' => array(
          'type' => 'varchar',
          'length' => 32,
          'not null' => TRUE,
        ),
      ),
      MigrateDestinationEntityAPI::getKeySchema('commerce_product', 'obraz')
    );

    // Create a MigrateSource object.
    $this->source = new MigrateSourceCSV(drupal_get_path('module', 'commerce_kickstart_lite_product') . '/import/obrazy-varianty.csv', $this->csvcolumns(), array('header_rows' => 1), $this->fields());

    $this->destination = new MigrateDestinationEntityAPI('commerce_product', 'obraz');

    $this->addFieldMapping('title', 'title');
    $this->addFieldMapping('sku', 'sku');
    $this->addFieldMapping('commerce_price', 'price');

    // Images
    $this->addFieldMapping('field_images', 'product_images');
    $this->addFieldMapping('field_images:file_replace')
      ->defaultValue(FILE_EXISTS_REPLACE);
    $this->addFieldMapping('field_images:source_dir')
      ->defaultValue(drupal_get_path('module', 'commerce_kickstart_lite_product') . '/import/images');

    $this->addFieldMapping('uid', 'uid');
    $this->addFieldMapping('field_typ_obrazu', 'typ_obrazu');
    $this->addFieldMapping('field_bezna_cena', 'bezna_cena');
    $this->addFieldMapping('field_doba_dodani', 'doba_dodani');
    $this->addFieldMapping('field_rozmery_obrazu', 'rozmery_obrazu');
    $this->addFieldMapping('language', 'language');
    $this->addFieldMapping('field_s_hodinami', 'hodiny');
    $this->addFieldMapping('field_umisteni_hodin', 'umisteni');
    $this->addFieldMapping('field_tagy', 'tagy');
    $this->addFieldMapping('field_description', 'popis');
    $this->addFieldMapping('field_description:summary', 'excerpt');
    $this->addFieldMapping('commerce_stock', 'sklad');
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
    $columns[8] = array('language', 'Jazyk');
    $columns[9] = array('umisteni', 'Umisteni');
    $columns[10] = array('sklad', 'Sklad');
    $columns[11] = array('popis', 'Description');
    $columns[12] = array('tags', 'Tagy');
    $columns[13] = array('hodiny', 'Hodiny');
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
    $row->tagy = explode(', ', $row->tags);
  }
}

class CommerceKickstartObrazyNodes extends CommerceKickstartMigration {

  public function __construct() {
    parent::__construct();
    $this->description = t('Import stránek (nodes) s obrazy.');

    $this->dependencies = array(
      'CommerceKickstartObrazyVarianty',
    );

    // Create a map object for tracking the relationships between source rows
    $this->map = new MigrateSQLMap($this->machineName,
      array(
        'title' => array(
          'type' => 'varchar',
          'length' => 255,
          'not null' => TRUE,
        ),
      ),
      MigrateDestinationNode::getKeySchema('obraz')
    );

    // Create a MigrateSource object.
    $this->source = new MigrateSourceCSV(drupal_get_path('module', 'commerce_kickstart_lite_product') . '/import/obrazy-nodes.csv', $this->csvcolumns(), array('header_rows' => 1));

    $this->destination = new MigrateDestinationNode('obraz');

    $this->addFieldMapping('uid', 'uid')->defaultValue(1);

    $this->addFieldMapping('title', 'title');
    $this->addFieldMapping('body', 'description');
    $this->addFieldMapping('body:summary', 'excerpt');
    $this->addFieldMapping('field_product_category', 'category');
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