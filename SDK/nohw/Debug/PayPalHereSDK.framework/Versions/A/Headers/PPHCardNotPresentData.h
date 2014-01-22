//
//  PayPalHereSDK
//
//  Copyright (c) 2012 PayPal. All rights reserved.
//

#import <Foundation/Foundation.h>

typedef NS_ENUM(NSInteger, PPHCreditCardType) {
    ePPHCreditCardTypeUnknown = 0,
    ePPHCreditCardTypeVisa = 1,
    ePPHCreditCardTypeMastercard = 2,
    ePPHCreditCardTypeDiscover = 3,
    ePPHCreditCardTypeAmEx = 4,
    ePPHCreditCardTypeJCB = 5,
    ePPHCreditCardTypeMaestro = 6,
    ePPHCreditCardTypePayPal = 7
};


/*!
 * A container for manually entered (or scanned) card data
 */
@interface PPHCardNotPresentData : NSObject
/*!
 * The full card number
 */
@property (nonatomic,strong) NSString *cardNumber;
/*!
 * Expiration date of the card, only month/year matter
 */
@property (nonatomic,strong) NSDate *expirationDate;
/*!
 * Security code on the card
 */
@property (nonatomic,strong) NSString *cvv2;

/*! If available, the postal code for the card holder. Certain regions do not
 * require this information
 */
@property (nonatomic,strong) NSString *postalCode;

/*! Set to YES if this information was acquired via card scanning. There is no
 * change in fees compared to manual entry as of this writing.
 */
@property (nonatomic) BOOL scanned;

/*!
 * @returns YES for valid card number
 */
@property (nonatomic, readonly) BOOL isValid;

/*!
 * @returns PPHCardType of entered card
 */
@property (nonatomic, readonly) PPHCreditCardType cardType;

@end