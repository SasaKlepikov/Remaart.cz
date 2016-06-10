<article<?php print $attributes; ?>>
    <div<?php print $content_attributes; ?>>
        <?php
        // We hide the comments and links.
        hide($content['comments']);
        hide($content['links']);
        hide($content['product:commerce_price']);
        hide($content['product:field_bezna_cena']);
        ?>
        <div class="image-preview-wrapper">
            <?php
            print render($content['product:field_images']);
            ?>
            <?php
            if (isset($content['product:field_tip_na_darek'][0]['#markup']) && $content['product:field_tip_na_darek'][0]['#markup'] || isset($content['product:field_doporucujeme'][0]['#markup']) && $content['product:field_doporucujeme'][0]['#markup'] || isset($content['product:field_sleva']['#object']) && $content['product:field_sleva']['#object']):
              ?>
              <div class="extra-buttons-wrapper">
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
        <div class="other-wrapper">
            <?php
            print render($content['title_field']);
            
            if (isset($content['product:field_bezna_cena']) && $content['product:field_bezna_cena']) {
              print render($content['product:field_bezna_cena']);
            }

            print "<div class='product-list-line'><strong>Naše cena:</strong> " . render($content['product:commerce_price']) . "</div>";
            ?>
        </div>
    </div>
</article>