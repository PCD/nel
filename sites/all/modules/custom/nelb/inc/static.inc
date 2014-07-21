<?php
/**
 * Get Category Tid.
 */
function nelb_get_category_tid($tid) {
  $tids = array(
    5, // Hoy en Nayarit
    6, // - Municipios
    7, // - Nayarit
    
    8, // - Tepic
    1, // Mas Noticias
    
    90 => 13, // Opinión
    9, // Portada
    144, // Reporte Especial
    105 => 15, // Sucesos
    103 => 174, // Política y Gobierno
    104 => 175, // Sociedad
    134 => 176, // La Feria
    125 => 177, // Coberturas
    136 => 178, // Clima y Naturaleza
    14, // Televisión
    16, // Voto 2014
    
    162, // Voto 2011
    107 => 163, // - Aspirantes
    108 => 164, // - Cobertura
    109 => 165, // - Encuestas
    127 => 166, // - Personajes
    
    145, // Voto 2012
    128 => 146, // - Presidenciables
    130 => 148, // - Cobertura Nacional
    129 => 147, // - Cobertura Local
    135 => 12, // Sorprendente
    
    149, // Cartón Digital
    123 => 150, // - El Montachón
    
    151, // Global
    121 => 152, // - Medio Ambiente
    113 => 3, // - Mundo
    117 => 11, // Tecnología
    
    153, // Entretenimiento
    115 => 154, // - Deportes
    116 => 155, // - Espectáculos
    122 => 156, // - Cultura
    137 => 157, // - Estilos

    158, // México
    111 => 159, // - Estados
    110 => 160, // - Kiosko
    118 => 161, // - Cartera
    112 => 4, // - Nacional
    
    167, // Especiales
    94 => 168, // - El escándalo de Gándara
    92 => 169, // - El Fajamaleón
    91 => 170, // - Bellezas
    120 => 2, // - ANIMALERIAS
    132 => 10, // - Centenario
    96 => 171, // - Tendencias
    106 => 172, // - Bicentenario
    126 => 173, // - Newsflash
    
    179, // Artículos
    88 => 180, // - Noticias
    93 => 181, // - Entrevistas
    89 => 182, // - Reportajes
    95 => 183, // - Coberturas
    
    // Autores
    142 => 13, // Emilio Mu Rivera
    143 => 13, // Héctor M. Benítez
    139 => 13, // Miguel González Ibarra
    114 => 13, // Salvador Mancillas
    141 => 13, // Noel Adolfo Corona
    102 => 13, // Invitados
    140 => 13, // Emiliano Zapata Sandoval
    138 => 13, // Jenaro Villamil
    119 => 13, // Francisco Javier Castellón
    131 => 13, // Jorge Enrique González
    133 => 13, // Raúl Pérez González
    98 => 13, // Luis Alberto Alcaraz
    124 => 13, // Duende Preguntón
    100 => 13, // Ana Pérez-Díaz
    101 => 13, // Guillermo Méndez
    99 => 13, // Luis Ignacio Palacios
    97 => 13, // Antonio Tello
  );
  
  if ( isset($tids[$tid]) ) {
    return $tids[$tid];
  }
  return false;
}

/**
 * Get Author Tid.
 */
function nelb_get_autor_tid($tid) {
  $tids = array(
    // Autores
    142 => 184, // Emilio Mu Rivera
    143 => 185, // Héctor M. Benítez
    139 => 186, // Miguel González Ibarra
    114 => 187, // Salvador Mancillas
    141 => 188, // Noel Adolfo Corona
    102 => 189, // Invitados
    140 => 190, // Emiliano Zapata Sandoval
    138 => 191, // Jenaro Villamil
    119 => 192, // Francisco Javier Castellón
    131 => 193, // Jorge Enrique González
    133 => 194, // Raúl Pérez González
    98 => 195, // Luis Alberto Alcaraz
    124 => 196, // Duende Preguntón
    100 => 197, // Ana Pérez-Díaz
    101 => 198, // Guillermo Méndez
    99 => 199, // Luis Ignacio Palacios
    97 => 200, // Antonio Tello
  );
  
  if ( isset($tids[$tid]) ) {
    return $tids[$tid];
  }
  return false;
}