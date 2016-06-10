<article<?php print $attributes; ?>>
    <div id="product-detail-page">
        <div id="product-title" class="container-24 grid-24 clearfix">
            <?php print render($content['title_field']); ?>
        </div>
        <div id="product-image" class="container-24 grid-14 prefix-1 clearfix">
            <?php print render($content['product:field_images']); ?>
        </div>
        <div id="product-info" class="container-24 grid-10 prefix-1">
            <div<?php print $content_attributes; ?>>
                <?php
                print render($content['product:sku']);
                if (isset($content['product:field_typ_obrazu']) && $content['product:field_typ_obrazu'] || $content['product:field_s_hodinami'] || $content['product:field_umisteni_hodin']):
                  ?>
                  <div class="typ-obrazu">
                      <?php
                      print render($content['product:field_typ_obrazu']);
                      print render($content['product:field_s_hodinami']);
                      print render($content['product:field_umisteni_hodin']);
                      ?>
                  </div>
                  <?php
                endif;
                print render($content['product:field_doba_dodani']);
                print render($content['product:field_rozmery_obrazu']);
                print render($content['product:field_bezna_cena']);
                print render($content['product:commerce_price']);
                print render($content['field_product']);
                ?>
            </div>
            <?php
            if (isset($content['product:field_tip_na_darek'][0]['#markup']) && $content['product:field_tip_na_darek'][0]['#markup'] || isset($content['product:field_doporucujeme'][0]['#markup']) && $content['product:field_doporucujeme'][0]['#markup'] || isset($content['product:field_sleva']['#object']) && $content['product:field_sleva']['#object']):
              ?>
              <div id="extra-buttons">
                  <?php
                  if (isset($content['product:field_tip_na_darek'][0]['#markup']) && $content['product:field_tip_na_darek'][0]['#markup']):
                    print render($content['product:field_tip_na_darek']);
                  endif;
                  
                  if (isset($content['product:field_doporucujeme'][0]['#markup']) && $content['product:field_doporucujeme'][0]['#markup']):
                    print render($content['product:field_doporucujeme']);
                  endif;
                  
                  if (isset($content['product:field_sleva']['#object']) && $content['product:field_sleva']['#object']):
                    print render($content['product:field_sleva']);
                  endif;
                  ?>
              </div>
              <?php
            endif;
            ?>
        </div>
        <div id="product-other-info" class="container-24 grid-24 clearfix">
            <?php
            // We hide the comments and links now so that we can render them later.
            hide($content['comments']);
            hide($content['links']);

            $tabs = array();

            // If exist product description
            if (isset($content['product:field_description']['#object']) && $content['product:field_description']['#object']) {
              $tabs[] = array('title' => t('Popis'), 'contents' => array('#markup' => render($content['product:field_description'])));
            }

            // If exist product parameters
            if (isset($content['product:field_nahledy']['#object']) && $content['product:field_nahledy']['#object']) {
              $tabs[] = array('title' => t('Náhledy'), 'contents' => array('#markup' => render($content['product:field_nahledy'])));
            }

            // Add comments
            if (isset($content['comments']['comment_form']) && $content['comments']['comment_form'] || isset($content['comments']['comments']) && $content['comments']['comments']) {
              $tabs[] = array('title' => t('Komentáře'), 'contents' => array('#markup' => render($content['comments'])));
            }

            // If exist parameters of pieces
            if (isset($content['product:field_rozmery_dilu_obrazu']['#object']) && $content['product:field_rozmery_dilu_obrazu']['#object']) {
              $tabs[] = array('title' => t('Rozměry dílů'), 'contents' => array('#markup' => render($content['product:field_rozmery_dilu_obrazu'])));
            }

            // If exist materials
            if (isset($content['field_podklady']) && $content['field_podklady'] && $is_admin) {
              $tabs[] = array('title' => t('Podklady'), 'contents' => array('#markup' => views_embed_view('podklady_k_obrazu', 'block')));
            }

            $qtname = 'product_detail_tabs_info';
            $overrides = array('sorted' => TRUE, 'ajax' => FALSE);
            $renderqtabs = quicktabs_build_quicktabs($qtname, $overrides, $tabs);
            print drupal_render($renderqtabs);
            ?>
        </div>
    </div>
</article>
